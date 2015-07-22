#include "asm_instruction.h"

// Constructors of special kinds of operands.
operand_pointer new_register_operand(register_id reg){
	operand_pointer op = operand_pointer(new operand);
	op->op_addr = operand_addressing::REGISTER;
	op->value.reg = reg;

	return op;
}

// TODO: hago un procedimiento para tipo de valor inmediato? o a estas alturas
// deberíamos tratar todo como cadenas de bits?
operand_pointer new_immediate_int_operand(int imm_int){
	operand_pointer op = operand_pointer(new operand);
	op->op_addr = operand_addressing::IMMEDIATE;
	op->value.imm.ival = imm_int;

	return op;
}

operand_pointer new_memory_operand(unsigned int offset, unsigned int base,
								   unsigned int index,
								   unsigned int scale){

	operand_pointer op = operand_pointer(new operand);
	op->op_addr = operand_addressing::MEMORY;
	op->value.mem.offset = offset;
	op->value.mem.base = base;
	op->value.mem.index = index;
	op->value.mem.scale = scale;

	return op;
}

operand_pointer new_label_operand(std::string label){

	operand_pointer op = operand_pointer(new operand);
	op->op_addr = operand_addressing::NONE;
	op->value.label = label;

	return op;
}

// Constructors of instructions.
asm_instruction_pointer new_mov_instruction(address_pointer source,
								address_pointer destination,
								data_type ops_type){

	#ifdef __DEBUG
		assert(_destination->op_addr == operand_addressing::REGISTER ||
			   _destination->op_addr == operand_addressing::MEMORY);
	#endif

	// TODO: precondición: source y destination se refieren a valores del
	// mismo tipo.
	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::MOV;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = ops_type;
	inst->source = source;
	inst->destination = destination;

	return inst;

}

asm_instruction_pointer new_mul_instruction(address_pointer source,
								address_pointer destination,
								data_type ops_type){

	#ifdef __DEBUG
		assert(destination->op_addr == operand_addressing::REGISTER ||
			   destination->op_addr == operand_addressing::MEMORY);
	#endif

	// TODO: precondición: source y destination se refieren a valores del
	// mismo tipo
	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::MUL;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = ops_type;
	inst->source = source;
	inst->destination = destination;

	return inst;
}

asm_instruction_pointer new_add_instruction(address_pointer source,
								address_pointer destination,
								data_type ops_type){

	#ifdef __DEBUG
		assert(destination->op_addr == operand_addressing::REGISTER ||
			   destination->op_addr == operand_addressing::MEMORY);
	#endif

	// TODO: precondición: source y destination se refieren a valores del
	// mismo tipo
	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::ADD;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = ops_type;
	inst->source = source;
	inst->destination = destination;

	return inst;
}

asm_instruction_pointer new_sub_instruction(address_pointer source,
								address_pointer destination,
								data_type ops_type){

	#ifdef __DEBUG
		assert(destination->op_addr == operand_addressing::REGISTER ||
			   destination->op_addr == operand_addressing::MEMORY);
	#endif

	// TODO: precondición: source y destination se refieren a valores del
	// mismo tipo
	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::SUB;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = ops_type;
	inst->source = source;
	inst->destination = destination;

	return inst;
}

asm_instruction_pointer new_div_instruction(address_pointer dividend,
								data_type ops_type){

	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::DIV;
	inst->ops_type = ops_type;
	inst->source = dividend;

	return inst;
}

asm_instruction_pointer new_shr_instruction(address_pointer imm,
											address_pointer destination,
											data_type ops_type){

	#ifdef __DEBUG
		assert(imm->op_addr == operand_addressing::IMMEDIATE &&
			   (destination->op_addr == operand_addressing::REGISTER ||
			    destination->op_addr == operand_addressing::MEMORY));
	#endif

	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::SHR;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = ops_type;
	inst->source = imm;
	inst->destination = destination;

	return inst;
}

asm_instruction_pointer new_neg_instruction(address_pointer destination,
											data_type ops_type){

	#ifdef __DEBUG
		assert(destination->op_addr == operand_addressing::REGISTER ||
			   destination->op_addr == operand_addressing::MEMORY);
	#endif

	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::NEG;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = ops_type;
	inst->destination = destination;

	return inst;
}

asm_instruction_pointer new_jmp_instruction(std::string label){
	asm_instruction_pointer inst = asm_instruction_pointer(new asm_instruction);
	inst->op = operation::JMP;
	// TODO: cómo determino el tipo de información de source?
	inst->ops_type = data_type::NONE;
	// TODO: notar que está más piola esta forma de definir el constructor
	// de instrucciones, sin exigirle al usuario que llame a
	// new_++++_operand para crear el tipo correcto de operando...
	inst->destination = new_label_operand(label);

	return inst;
}
