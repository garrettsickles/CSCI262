#include "list.h"

int main(){
    
	// create a list
	list my_list;
    
	// insert some stuff at the head
	my_list.insert_at_head('t');
	my_list.insert_at_head('a');
	my_list.insert_at_head('d');
    
	// insert some stuff at the tail
	my_list.insert_at_tail('a');
	my_list.insert_at_tail('s');
    
	// print the structure of the list
	my_list.print_structure();
	// print the contents of the list
	my_list.print_list();
    
	// remove the last element in the list
	my_list.remove_from_tail();
    
	my_list.print_structure();
	my_list.print_list();
    
	// remove the first element in the list
	my_list.remove_from_head();
    
	my_list.print_structure();
	my_list.print_list();
    
	// we can't delete more nodes than we have in the list so we need to
	// make sure that we don't have a null pointer exception
	my_list.remove_from_head();
	my_list.remove_from_head();
	my_list.remove_from_head();
	my_list.remove_from_head();
	my_list.remove_from_head();
	my_list.remove_from_tail();
	my_list.remove_from_tail();
	my_list.print_list();
    
    
    
	return 0;
}