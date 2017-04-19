#pragma once

template <typename T>
T min(T&& head, T&& tail...) {
	T t = min(tail);
	return head > t ? t : head;
}

template <typename T>
T min(T&& val) {
	return val;
}

template <typename T>
T max(T&& head, T&& tail...) {
	T t = max(tail);
	return head < t ? t : head;
}

template <typename T>
T max(T&& val) {
	return val;
}

template <typename T>
T clamp(T&& what, T&& from, T&& to) {
	return min(max(what, from), to);
}