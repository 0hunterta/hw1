#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) {
	if(empty()) {
		Item* newItem = new Item();
		newItem->first = 0;
		newItem->last = 1;
		newItem->val[0] = val;
		head_ = newItem;
		tail_ = newItem;
		size_ = 1;
	}
	else {
		if(tail_->last < ARRSIZE) {
			tail_->val[tail_->last] = val;
			tail_->last++;
			size_++;
		}
		else {
			Item* newItem = new Item();
			newItem->first = 0;
			newItem->last = 1;
			newItem->val[0] = val;
			newItem->prev = tail_;
			tail_->next = newItem;
			tail_  = newItem;
			size_++;
		}
	}
}
void ULListStr::pop_back() {
	if(empty()) return;
	tail_->last--;
	size_--;
	if(tail_->first == tail_->last) {
		if(tail_ == head_) {
			delete tail_;
			head_ = NULL;
			tail_ = NULL;
		}
		else {
			Item* temp = tail_;
			tail_ = tail_->prev;
			tail_->next = NULL;
			delete temp;
		}
	}
}
void ULListStr::push_front(const std::string& val) {
	if(empty()) {
                Item* newItem = new Item();
                newItem->first = ARRSIZE/2;
                newItem->last = newItem->first +1;
                newItem->val[newItem->first] = val;
                head_ = newItem;
                tail_ = newItem;
                size_ = 1;
        }
        else {
                if(head_->first > 0) {
			head_->first--;
			head_->val[head_->first] = val;
                        size_++;
                }
                else {
                        Item* newItem = new Item();
                        newItem->first = ARRSIZE-1;
                        newItem->last = ARRSIZE;
                        newItem->val[newItem->first] = val;
                        newItem->next = head_;
                        head_->prev = newItem;
                        head_  = newItem;
                        size_++;
                }
	}
}
void ULListStr::pop_front() {
	if(empty()) return;
        head_->first++;
        size_--;
        if(head_->first == head_->last) {
                if(tail_ == head_) {
                        delete head_;
                        head_ = NULL;
                        tail_ = NULL;
                }
                else {
                        Item* temp = head_;
                        head_ = head_->next;
                        head_->prev = NULL;
                        delete temp;
                }
        }
}
std::string const & ULListStr::back() const {
	if(empty()) throw std::runtime_error("List is empty");
	return tail_->val[tail_->last-1];
}
std::string const & ULListStr::front() const {
	if(empty()) throw std::runtime_error("List is empty");
	return head_->val[head_->first];
}
std::string* ULListStr::getValAtLoc(size_t loc) const {
	if(loc>=size_) return NULL;
	Item* curr = head_;
	size_t currIdx = 0;
	while(curr != NULL) {
		size_t span = curr->last - curr->first;
		if(loc < (currIdx+span)) {
			size_t offset = loc - currIdx;
			return &curr->val[curr->first + offset];
		}
		currIdx += span;
		curr = curr->next;
	}
	return NULL;
}
void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
