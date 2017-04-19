#pragma once

#include <iterator>
#include <type_traits>
#include <cstddef>
//#include <optional>


template <typename T>
class Range {

	struct Iterator {

		using value_type = T;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		Iterator(T val, T step, bool neg) : _val(std::move(val)), _step(std::move(step)), _negative(neg) {}

		bool operator==(const Iterator& o) const { return _negative ? _val <= o._val : _val >= o._val; } // TODO - Unsigned range with negative step to 0

		bool operator!=(const Iterator& o) const { return !(*this == o); }

		const T& operator*() const { return _val; }
		const T* operator->() const { return &_val; }

		Iterator& operator++() {
			_negative ? _val -= _step : _val += _step;
			return *this;
		}

		Iterator operator++(int) {
			auto copy(*this);
			++*this;
			return copy;
		}

	private:
		friend Range;
		T _val;
		T _step;
		bool _negative;
	};

public:
	Range(T from, T to, T step) :
		_from(std::move(from)),
		_to(std::move(to)),
		_step(std::move(step)) { }

	using iterator = Iterator;
	using const_iterator = Iterator;

	T step() const { return _step; }

	bool negative() const { return _from > _to; }

	iterator begin() const { return Iterator(_from, _step, _from > _to); }
	iterator end() const { return Iterator(_to, _step, _from > _to); }

private:
	T _from;
	T _to;
	T _step;
};

template< typename T >
auto range(T from, T to, T step) {
	return Range< T >(std::move(from), std::move(to), std::move(step));
}

template< typename T >
auto range(T from, T to) {
	return range(std::move(from), std::move(to), T(1));
}

template< typename T >
auto range(T to) {
	return range(T(0), std::move(to));
}

template <typename It, typename Pred>
class Filter {

	struct Iterator {

		using value_type = typename It::value_type;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = typename It::difference_type;
		using pointer = typename It::pointer;
		using reference = typename It::reference;

		Iterator(It val, It end, Pred pred) : _iter(val), _end(end), _pred(pred) {}

		bool operator==(const Iterator& o) const { return _iter == o._iter; }

		bool operator!=(const Iterator& o) const { return !(*this == o); }

		reference operator*() const { return *_iter; }
		pointer operator->() const { return _iter.operator->(); }

		Iterator& operator++() {
			do {
				++_iter;
			} while (!_pred(*_iter) || (_iter != _end));

			return *this;
		}

		Iterator operator++(int) {
			auto copy(*this);
			++*this;
			return copy;
		}

	private:
		It _iter;
		It _end;
		Pred _pred;
	};

public:
	using iterator = Iterator;
	using const_iterator = Iterator;

	Filter(It begin, It end, Pred pred) : _begin(begin), _end(end), _pred(pred) {}

	iterator begin() const { return Iterator(_begin, _end, _pred); }
	iterator end() const { return Iterator(_end, _end, _pred); }

private:
	friend Iterator;

	It _begin;
	It _end;
	Pred _pred;
};

template <typename It, typename Pred>
auto filter(It begin, It end, Pred pred) { return Filter<It, Pred>(begin, end, pred); }

template <typename C, typename Pred>
auto filter(C& container, Pred pred) { return filter(container.begin(), container.end(), pred); }
