#pragma once
#include<tuple>

template <int ... Args>
struct layout_map{
    static constexpr int length=sizeof...(Args);
    static const constexpr int layout_vector[sizeof...(Args)]={Args...};

    template <int I>
    static constexpr int at() {
		static_assert(I<length, "error in accessing the layout map, index to alrge");
		static_assert(I>=0, "error in accessing the layout map, negative index");
        return layout_vector[ I ];
    }

    template <int I>
    static auto constexpr select(int const* dims) {
		static_assert(I<length, "error in layout map's select function, index to large");
		static_assert(I>=0, "error in layout map's select function, negative index");
        return  dims[layout_vector[I]];
    }

    template <int I, typename ... T>
    static auto constexpr select(T & ... args) {
		static_assert(I<length, "error in layout map's select function, index too large");
		static_assert(I>=0, "error in layout map's select function, negative index");
		static_assert(sizeof...(T)==length, "wrong number of arguments to layout_map::select");
        return  std::get<layout_vector[I]>( std::make_tuple(args ...) );
    }
};
