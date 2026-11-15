#include <alloca.h>
#include <cstdint>

#include <cstddef>
#include <iostream>
#include <new>
#include <ostream>
#include <utility>

class Arena {
public:
	Arena(std::size_t size)
	    : m_size(size) {
		m_buffer = reinterpret_cast<std::byte*>(::operator new(size));
	}

	~Arena() {
		::operator delete(m_buffer);
	}

	void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) {
		uintptr_t current { reinterpret_cast<uintptr_t>(m_buffer + m_offset) };
		uintptr_t aligned { (current + alignment - 1) & ~(alignment - 1) };
		std::size_t padding { aligned - current };

		if (m_offset + size + padding > m_size) {
			return nullptr;
		}

		m_offset += padding;
		void* result { m_buffer + m_offset };
		m_offset += size;

		return result;
	}

	template <typename T, typename... Args>
	T* allocate(Args&&... args) {
		void* object { allocate(sizeof(T), alignof(T)) };

		if (object == nullptr)
			return nullptr;

		return new (object) T { std::forward<Args>(args)... };
	}

	void reset() {
		m_offset = 0;
	}

private:
	std::byte* m_buffer {};
	std::size_t m_size {};
	std::size_t m_offset {};
};

int main() {
	Arena arena { 1024 };

	auto* x { arena.allocate<int>(4) };
	auto* y { arena.allocate<int>(8) };
	auto* z { arena.allocate<int>(16) };

	std::cout << *x << std::endl;

	arena.reset();

	std::cout << *x << std::endl;
	arena.allocate<int>(8);
	std::cout << *x << std::endl;
}

