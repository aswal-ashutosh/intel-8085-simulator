#pragma once
#include<map>
#include<string>
#include"converter.h"
#include"constants.h"

class Register
{
public:
	static std::map<std::string, int> Main;
	static int iPC, PC, SP;

	class Flag
	{
	public:
		static bool SF, ZF, AC, PF, CY;
	};


	static int HL();

	static int BC();

	static int DE();

	static int PSW();

	static void UpdateFlags(int, bool);

	static void Clear();
};

int Register::iPC = 0;
int Register::PC = 0;
int Register::SP = 0xffff;
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

int Register::PSW()// Return 16 bit value consisting of A & Flag Register
{	
	/*
		Flag Register Structure => [S][Z][-][AC][-][P][-][CY]
									7  6  5  4   3  2  1   0
	*/
	int F = 0;
	if (Register::Flag::CY)
	{
		F |= (1 << 0);
	}
	if (Register::Flag::PF)
	{
		F |= (1 << 2);
	}
	if (Register::Flag::AC)
	{
		F |= (1 << 4);
	}
	if (Register::Flag::ZF)
	{
		F |= (1 << 6);
	}
	if (Register::Flag::SF)
	{
		F |= (1 << 7);
	}

	return (Register::Main[REGISTER::A] << 8) | F;

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
	Register::iPC = 0;
	Register::PC = 0;
	Register::SP = 0xffff;

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