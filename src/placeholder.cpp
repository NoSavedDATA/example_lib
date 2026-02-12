#include<iostream>
#include<string>

#include"../../../src/nsk_cpp.h"
#include "placeholder.h"

DT_placeholder::DT_placeholder() {}

void DT_placeholder::New(int x, int y) {
	this->x=x;
	this->y=y;
}


extern "C" DT_placeholder *placeholder_Create(Scope_Struct *scope_struct, int x, int y) {
	DT_placeholder *val = newT<DT_placeholder>(scope_struct, "placeholder");
	val->New(x, y);
    return val;
}


extern "C" void placeholder_print(Scope_Struct *scope_struct, DT_placeholder *val) {
	std::cout << "placeholder x: " << val->x << ", y: " << val->y << std::endl;
}

extern "C" DT_placeholder *placeholder_placeholder_add(Scope_Struct *scope_struct, DT_placeholder *x, DT_placeholder *y) {
	DT_placeholder *ret = newT<DT_placeholder>(scope_struct, "placeholder");
	ret->New(x->x+y->x, x->y+y->y);
	return ret;
}

extern "C" void placeholder_add(Scope_Struct *scope_struct, DT_placeholder *x, int y) {
	x->x+=y;
	x->y+=y;
}


extern "C" DT_placeholder *placeholder_int_add(Scope_Struct *scope_struct, DT_placeholder *x, int y) {
	DT_placeholder *ret = newT<DT_placeholder>(scope_struct, "placeholder");
	ret->New(x->x+y, x->y+y);
	return ret;
}

extern "C" DT_placeholder *placeholder_Copy(Scope_Struct *scope_struct, DT_placeholder *incoming) {
	DT_placeholder *ret = newT<DT_placeholder>(scope_struct, "placeholder");
	ret->New(incoming->x, incoming->y);
	return ret;
}

extern "C" DT_placeholder *add_int_to_placeholder(Scope_Struct *scope_struct, DT_placeholder *px, int z, int w)
{
    // $> placeholder $ z=3 $ w=2 $

    int x = px->x + z + w;
    int y = px->y + z + w;

       
    DT_placeholder *placeholder = newT<DT_placeholder>(scope_struct, "placeholder");
    placeholder->New(x, y);

    return placeholder;
}

extern "C" DT_array *make_placeholder_sequence(Scope_Struct *scope_struct, DT_placeholder *x, DT_placeholder *y, DT_placeholder *z) {
	// $> array<placeholder> $ y = new placeholder(6,7) $ z = new placeholder(6,7) $
	DT_array *array = newT<DT_array>(scope_struct, "array");
	array->New(3, "placeholder");

	DT_placeholder **placeholder_array = static_cast<DT_placeholder**>(array->data);
	placeholder_array[0]=x;
	placeholder_array[1]=y;
	placeholder_array[2]=z;

	return array;
}

extern "C" DT_map *make_placeholder_map(Scope_Struct *scope_struct, DT_placeholder *x, DT_placeholder *y, DT_placeholder *z) {
	// $> map<str, placeholder> $ x = new placeholder(8,8) $ y = new placeholder(6,7) $ z = new placeholder(9,10) $
	DT_map *map = newT<DT_map>(scope_struct, "map");
	map->New(3, 8, 8, "str", "placeholder");
	map->insert(scope_struct, "one", x);
	map->insert(scope_struct, "two", y);
	map->insert(scope_struct, "three", z);
	map->insert(scope_struct, "z", x);
	map->insert(scope_struct, "zz", x);
	map->insert(scope_struct, "zzz", x);

    z = map->get<DT_placeholder*>("two");


	return map;
}

extern "C" DT_list *ret_placeholder_int(Scope_Struct *scope_struct) {
	DT_list *list = newT<DT_list>(scope_struct, "list");
	DT_placeholder *x = newT<DT_placeholder>(scope_struct, "placeholder");
	x->New(1,2);
	int y = 5;

	list->append(std::any((void*)x), "placeholder");
	list->append(y, "int");
	return list;
}

extern "C" void array_print_placeholder(Scope_Struct *scope_struct, DT_array *array) {
	int n = array->virtual_size;
	DT_placeholder **data = static_cast<DT_placeholder**>(array->data);

	for(int i=0; i<n; ++i) {
		std::cout << "v[" << i << "]: " << data[i]->x << ", " << data[i]->y << std::endl;
	}
}


extern "C" int multiply_all(Scope_Struct *scope_struct, int x, ...)
{
  va_list args;
  va_start(args, x);
 
  int y=1;

  for (int i=0; i<10; i++)
  {
    y = y * x;
    int x = va_arg(args, int);
    if (x==TERMINATE_VARARG)
      break;
  }
  va_end(args);
  return y;
}




extern "C" void placeholder_Clean_Up(void *ptr) {

}
