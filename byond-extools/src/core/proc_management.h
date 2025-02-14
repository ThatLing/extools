#pragma once
#include "core.h"
#include <string>
#include <vector>
#include <unordered_map>

typedef trvh(*ProcHook)(Value* args, unsigned int args_len);

class Disassembly;

namespace Core
{
	struct Proc
	{
		Proc() {};
		Proc(std::string name);
		Proc(std::uint32_t id);
		std::string name;
		std::string simple_name;
		std::uint32_t id = 0;

		ProcArrayEntry* proc_table_entry = nullptr;
		ProcSetupEntry* setup_entry_bytecode = nullptr;
		ProcSetupEntry* setup_entry_varcount = nullptr;

		std::uint16_t bytecode_idx = 0;
		std::uint16_t varcount_idx = 0;

		std::uint32_t* original_bytecode_ptr = nullptr;

		void set_bytecode(std::vector<std::uint32_t>* new_bytecode);
		void set_bytecode(std::uint32_t* new_bytecode);
		std::uint32_t* get_bytecode();
		std::uint16_t get_bytecode_length();
		void reset_bytecode();

		std::uint16_t get_local_varcount();
		Disassembly disassemble();
		void assemble(Disassembly disasm);

		ProfileInfo* profile();
		void extended_profile();
		void hook(ProcHook hook_func);
		Value call(std::vector<Value>& arguments, Value usr = Value::Null(), Value src = Value::Null());

		bool operator<(const Proc& rhs) const
		{
			return id < rhs.id;
		}

		bool operator==(const Proc& rhs) const
		{
			return id == rhs.id;
		}

		operator int()
		{
			return id;
		}

		operator std::string()
		{
			return name;
		}
	};

	Proc get_proc(std::string name);
	Proc get_proc(unsigned int id);
	const std::vector<Proc>& get_all_procs();

	bool populate_proc_list();
	Disassembly disassemble_raw(std::vector<int> bytecode);
}

extern std::vector<Core::Proc> procs_by_id;
extern std::unordered_map<unsigned int, ProcHook> proc_hooks;
extern std::unordered_map<unsigned int, bool> extended_profiling_procs;