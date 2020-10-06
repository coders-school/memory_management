#pragma once
#include <atomic>
#include <iostream>
#include <vector>

template <typename T> class ControlBlock {

public:
  std::atomic<size_t> sharedRefsCounter_{1};
  std::atomic<size_t> weakRefsCounter_{0};
  void deleter(T *rawPtr) { delete rawPtr; };
};

template <typename T> class SharedPtr {

public:
  SharedPtr(T *rawPtr = nullptr);
  SharedPtr(SharedPtr<T> &&other) noexcept;      // move constructor
  SharedPtr(const SharedPtr<T> &other) noexcept; // copy constructor
  ~SharedPtr();
  T *get() const;
  T &operator*() const noexcept;
  T *operator->() const noexcept;
  SharedPtr<T> &operator=(const SharedPtr<T> &other) noexcept;
  explicit operator bool() const noexcept;
  void reset(T *NewRawPtr = nullptr);
  int use_count() const;

private:
  T *rawPtr_;
  ControlBlock<T> *ControlBlock_;
};

template <typename T>
SharedPtr<T>::SharedPtr(T *rawPtr)
    : rawPtr_(rawPtr) {
      ControlBlock_ = new ControlBlock<T>;
    }

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> && other) noexcept // move constructor
    : rawPtr_(other.rawPtr_), ControlBlock_(other.ControlBlock_) {
  other.rawPtr_ = nullptr;
  //other.ControlBlock_ = nullptr; // dont know why it dosent work
    }

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other) noexcept // copy constructor
    : rawPtr_(other.rawPtr_), ControlBlock_(other.ControlBlock_) {
  ControlBlock_->sharedRefsCounter_.exchange(
      ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) + 1,
      std::memory_order_relaxed);
}

template <typename T> SharedPtr<T>::~SharedPtr() {
  if (ControlBlock_->sharedRefsCounter_ >= 2) {
    ControlBlock_->sharedRefsCounter_.exchange(
        ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) - 1,
        std::memory_order_relaxed);
  } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
             ControlBlock_->weakRefsCounter_ == 0) {
    ControlBlock_->deleter(rawPtr_);
    //delete ControlBlock_; //why it makes problem??
  } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
             ControlBlock_->weakRefsCounter_ >= 1) {
    ControlBlock_->deleter(rawPtr_);
  }
}

template <typename T> T *SharedPtr<T>::get() const { return rawPtr_; }

template <typename T> T &SharedPtr<T>::operator*() const noexcept {
  return *rawPtr_;
}

template <typename T> T *SharedPtr<T>::operator->() const noexcept {
  return rawPtr_;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other) noexcept {
  if (other.rawPtr_ != rawPtr_) {
    if (ControlBlock_->sharedRefsCounter_ >= 2) {
      ControlBlock_->sharedRefsCounter_.exchange(
          ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) - 1,
          std::memory_order_relaxed);
      ControlBlock_ = other.ControlBlock_;
      ControlBlock_->sharedRefsCounter_.exchange(
          ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) + 1,
          std::memory_order_relaxed);
      rawPtr_ = other.rawPtr_;
      return *this;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ >= 1) {
      ControlBlock_->deleter(rawPtr_);
      rawPtr_ = other.rawPtr_;
      ControlBlock_ = other.ControlBlock_;
      ControlBlock_->sharedRefsCounter_.exchange(
          ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) + 1,
          std::memory_order_relaxed);
      return *this;
    } else if (ControlBlock_->sharedRefsCounter_ == 1 &&
               ControlBlock_->weakRefsCounter_ == 0) {
      rawPtr_ = other.rawPtr_;
      ControlBlock_ = other.ControlBlock_;
      ControlBlock_->sharedRefsCounter_.exchange(
          ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) + 1,
          std::memory_order_relaxed);
      return *this;
    } else
      return *this;
  } else
    return *this;
}

template <typename T> SharedPtr<T>::operator bool() const noexcept {
  return (this->get() != nullptr);
}

template <typename T> void SharedPtr<T>::reset(T *NewRawPtr) {
  if (ControlBlock_->sharedRefsCounter_ >= 2) {
    ControlBlock_->sharedRefsCounter_.exchange(
        ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed) - 1,
        std::memory_order_relaxed);
    ControlBlock_ = new ControlBlock<T>{};
    rawPtr_ = NewRawPtr;
  } else if (ControlBlock_->sharedRefsCounter_ == 1) {
    ControlBlock_->deleter(rawPtr_);
    rawPtr_ = NewRawPtr;
    ControlBlock_ = new ControlBlock<T>{};
  }
}

template <typename T> int SharedPtr<T>::use_count() const {
  return ControlBlock_->sharedRefsCounter_.load(std::memory_order_relaxed);
}