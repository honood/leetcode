// HoNooD
// 2024.05.07

// https://leetcode.com/problems/lru-cache/description/?envType=study-plan-v2&envId=top-interview-150 
// https://leetcode.com/problems/lru-cache/description/ 

#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>

using namespace std;
class LRUCache {
public:
	explicit LRUCache(int capacity) : capacity_{capacity} {
		query_.reserve(capacity);
	}

	int get(int key) {
		if (!query_.contains(key)) { // C++20 needed
			return -1;
		}

		auto it = query_[key];
		auto pair = *it;
		cache_.erase(it);
		cache_.emplace_front(pair.first, pair.second);
		query_[key] = cache_.begin();

		return pair.second;
	}

	void put(int key, int value) {
		if (query_.contains(key)) { // C++20 needed
			auto it = query_[key];
			query_.erase(it->first);
			cache_.erase(it);
			cache_.emplace_front(key, value);
			query_[key] = cache_.begin();
			return;
		}

		if (query_.size() < capacity_) {
			cache_.emplace_front(key, value);
			query_[key] = cache_.begin();
			return;
		}

		query_.erase(cache_.back().first);
		cache_.pop_back();
		cache_.emplace_front(key, value);
		query_[key] = cache_.begin();
	}

private:
	list<pair<int, int>> cache_{};
	unordered_map<int, decltype(cache_)::iterator> query_{};
	int capacity_{0};
};

int main(int argc, char* argv[]) {
	{
		LRUCache* lruCache = new LRUCache{2};
		{
			lruCache->put(1, 1);
			lruCache->put(2, 2);
			assert(lruCache->get(1) == 1);
			lruCache->put(3, 3);
			assert(lruCache->get(2) == -1);
			lruCache->put(4, 4);
			assert(lruCache->get(1) == -1);
			assert(lruCache->get(3) == 3);
			assert(lruCache->get(4) == 4);
		}
		delete lruCache;
	}

	{
		LRUCache* lruCache = new LRUCache{2};
		{
			lruCache->put(2, 1);
			lruCache->put(1, 1);
			lruCache->put(2, 3);
			lruCache->put(4, 1);
			assert(lruCache->get(1) == -1);
			assert(lruCache->get(2) == 3);
		}
		delete lruCache;
	}

	return 0;
}
