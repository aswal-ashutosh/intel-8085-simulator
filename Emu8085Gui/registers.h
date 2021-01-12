#pragma once
#include<map>
#include<string>
#include"converter.h"
#include"constants.h"

class Register
{
public:
	static std::map<std::string, int> Main;
	static int PC;

	class Flag
	{
	public:
		static bool SF, ZF, AC, PF, CY;
	};


	static int HL();

	static int BC();

	static int DE();

	static void UpdateFlags(int, bool);

	static void Clear();
};

int Register::PC = 0;
std::map<std::string, int> Register::Main = { {REGISTER::A, 0}, {REGISTER::B, 0}, {REGISTER::C ,0}, {REGISTER::D ,0}, {REGISTER::E ,0}, {REGISTER::H ,0}, {REGISTER::L ,0} };
bool Register::Flag::AC;
bool Register::Flag::CY;
bool Register::Flag::PF;
bool Register::Flag::SF;
bool Register::Flag::ZF;


int Register::HL()
{
	return (Main[REGISTER::H] << 8) | Main[REGISTER::L];
}

int Register::BC()
{
	return (Main[REGISTER::B] << 8) | Main[REGISTER::C];
}

int Register::DE()
{
	return (Main[REGISTER::D] << 8) | Main[REGISTER::E];
}

void Register::UpdateFlags(int aux, bool preserve_carry = false)
{
	if (!preserve_carry)
	{
		Register::Flag::CY = Register::Main[REGISTER::A] & (1 << 8); //@Carry Flag
	}

	Utility::_8Bit_Normalization(Register::Main[REGISTER::A]);

	Register::Flag::SF = Register::Main[REGISTER::A] & (1 << 7); //@Sign Flag

	Register::Flag::ZF = Register::Main[REGISTER::A] == 0; //@Zero Flag

	Register::Flag::AC = aux > 0xf; //@Aux Carry Flag

	Register::Flag::PF = !(Utility::_set_bits_count(Register::Main[REGISTER::A]) & 1); //@Pairty Flag
}


void Register::Clear()
{
	Register::PC = 0;

	Register::Flag::AC = false;
	Register::Flag::CY = false;
	Register::Flag::PF = false;
	Register::Flag::SF = false;
	Register::Flag::ZF = false;

	for (std::pair<const std::string, int>& reg : Main)
	{
		reg.second = 0;
	}
}