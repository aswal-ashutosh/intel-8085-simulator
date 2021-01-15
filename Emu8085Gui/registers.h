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
		static int FLAG;
	};


	static int HL();

	static int BC();

	static int DE();

	static void SyncFLAG();//Sync FLAG value when there is a change in any flag

	static void ReverseSyncFLAG();//Sync all flags when there is change in FLAG

	static int PSW();

	static void UpdateFlags(int, bool);

	static void Clear();
};

int Register::iPC = 0;
int Register::PC = 0;
int Register::SP = 0xffff;
std::map<std::string, int> Register::Main = { {REGISTER::A, 0}, {REGISTER::B, 0}, {REGISTER::C ,0}, {REGISTER::D ,0}, {REGISTER::E ,0}, {REGISTER::H ,0}, {REGISTER::L ,0} };
bool Register::Flag::AC = false;
bool Register::Flag::CY = false;
bool Register::Flag::PF = false;
bool Register::Flag::SF = false;
bool Register::Flag::ZF = false;
int Register::Flag::FLAG = 0x00;


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

int Register::PSW()
{
	return (Register::Main[REGISTER::A] << 8) | Register::Flag::FLAG;
}

void Register::SyncFLAG()// Return 16 bit value consisting of A & Flag Register
{	
	/*
		Flag Register Structure => [S][Z][-][AC][-][P][-][CY]
									7  6  5  4   3  2  1   0
	*/
	if (Register::Flag::CY)
	{
		Register::Flag::FLAG |= (1 << 0);
	}
	else
	{
		Register::Flag::FLAG &= ~(1 << 0);
	}

	if (Register::Flag::PF)
	{
		Register::Flag::FLAG |= (1 << 2);
	}
	else
	{
		Register::Flag::FLAG &= ~(1 << 2);
	}

	if (Register::Flag::AC)
	{
		Register::Flag::FLAG |= (1 << 4);
	}
	else
	{
		Register::Flag::FLAG &= ~(1 << 4);
	}

	if (Register::Flag::ZF)
	{
		Register::Flag::FLAG |= (1 << 6);
	}
	else
	{
		Register::Flag::FLAG &= ~(1 << 6);
	}

	if (Register::Flag::SF)
	{
		Register::Flag::FLAG |= (1 << 7);
	}
	else
	{
		Register::Flag::FLAG &= ~(1 << 7);
	}
}

void Register::ReverseSyncFLAG()
{
	/*
		Flag Register Structure => [S][Z][-][AC][-][P][-][CY]
									7  6  5  4   3  2  1   0
	*/

	Register::Flag::CY = Register::Flag::FLAG & (1 << 0);
	Register::Flag::PF = Register::Flag::FLAG & (1 << 2);
	Register::Flag::AC = Register::Flag::FLAG & (1 << 4);
	Register::Flag::ZF = Register::Flag::FLAG & (1 << 6);
	Register::Flag::SF = Register::Flag::FLAG & (1 << 7);
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

	Register::SyncFLAG();
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
	Register::Flag::FLAG = 0x00;

	for (std::pair<const std::string, int>& reg : Main)
	{
		reg.second = 0;
	}
}

