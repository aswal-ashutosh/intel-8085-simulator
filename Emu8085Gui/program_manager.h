#pragma once
#include<map>
#include<string>
#include<set>
#include"constants.h"
#include"validator.h"
#include"error_handler.h"
#include"converter.h"
#include"instruction.h"
#include"memory_manager.h"
//#include "registers.h";

class OpcodeInfo
{
public:
	const int opcode;
	const int size;
};


class ProgramManager
{

public:
	static std::map<std::string, int> Labels;
	static std::vector<Instruction> Program;
	static std::vector<int> CallStack;
	static std::set<std::string> JCallInstructions;

	static std::map<std::string, bool (*)(const Instruction&)> Load;
	static std::map<std::string, OpcodeInfo> OP_INFO;
	static std::map<std::string, std::vector<int>> LabelPosition;
	static std::map<std::string, int> LabelsAddress;
	static int Current_Address;

	static void LoadInstructionSet();


	static bool IsValid(const std::string& mnemonic);

	static bool IsJCallInstruction(const std::string& mnemonic);

	static bool MOV(const Instruction&);
	static bool MVI(const Instruction&);
	static bool LDA(const Instruction&);
	static bool STA(const Instruction&);
	static bool LHLD(const Instruction&);
	static bool SHLD(const Instruction&);
	static bool LXI(const Instruction&);
	static bool LDAX(const Instruction&);
	static bool STAX(const Instruction&);
	static bool XCHG(const Instruction&);

	//@Airthmatic Instrunction
	static bool ADD(const Instruction&);
	static bool ADC(const Instruction&);
	static bool ADI(const Instruction&);
	static bool ACI(const Instruction&);
	static bool SUB(const Instruction&);
	static bool SBB(const Instruction&);//Not sure about flags
	static bool SUI(const Instruction&);
	static bool SBI(const Instruction&);
	static bool INR(const Instruction&);//CY is not affected
	static bool INX(const Instruction&);//No flags are affected during the execution
	static bool DCR(const Instruction&);//CY is not affected
	static bool DCX(const Instruction&);//No flags are affected during the execution
	static bool DAD(const Instruction&);//only affect CY
	static bool DAA(const Instruction&);

	//@Logical Instructions

	static bool ANA(const Instruction&);
	static bool ANI(const Instruction&);
	static bool ORA(const Instruction&);
	static bool ORI(const Instruction&);
	static bool XRA(const Instruction&);
	static bool XRI(const Instruction&);
	static bool CMA(const Instruction&);//Flags are not affected by this instruction
	static bool RLC(const Instruction&);
	static bool RAL(const Instruction&);
	static bool RRC(const Instruction&);
	static bool RAR(const Instruction&);
	static bool STC(const Instruction&);
	static bool CMC(const Instruction&);
	static bool CMP(const Instruction&);
	static bool CPI(const Instruction&);

	//@Branching Instructions
	static bool JMP(const Instruction&);
	static bool JC(const Instruction&);
	static bool JNC(const Instruction&);
	static bool JZ(const Instruction&);
	static bool JNZ(const Instruction&);
	static bool JPE(const Instruction&);
	static bool JPO(const Instruction&);
	static bool JM(const Instruction&);
	static bool JP(const Instruction&);

	//subroutine
	static bool CALL(const Instruction&);
	static bool CNC(const Instruction&);
	static bool CC(const Instruction&);
	static bool CNZ(const Instruction&);
	static bool CZ(const Instruction&);
	static bool CPE(const Instruction&);
	static bool CPO(const Instruction&);
	static bool CP(const Instruction&);
	static bool CM(const Instruction&);
	static bool RET(const Instruction&);
	static bool RNC(const Instruction&);
	static bool RC(const Instruction&);
	static bool RZ(const Instruction&);
	static bool RNZ(const Instruction&);
	static bool RPE(const Instruction&);
	static bool RPO(const Instruction&);
	static bool RP(const Instruction&);
	static bool RM(const Instruction&);

	static bool HLT(const Instruction&);
	static bool NOP(const Instruction&);

	//OTHER

	static bool HALT;

	static bool Read(const std::string filePath);

	static void Run();

	static bool IsExistingLabel(const std::string&);

	static bool IsJCallInstruction(const std::string& mnemonic);

	static void Clear();

	//static bool CanRunFurther();//It will check whether there exist a instruction at Index = PC
};


std::vector<Instruction> ProgramManager::Program;
std::map<std::string, int> ProgramManager::Labels;
std::vector<int> ProgramManager::CallStack;
std::map<std::string, std::vector<int>> ProgramManager::LabelPosition;
std::map<std::string, int> ProgramManager::LabelsAddress;
std::map<std::string, bool (*)(const Instruction&)> ProgramManager::Load;
std::set<std::string> ProgramManager::JCallInstructions;
bool ProgramManager::HALT;
int ProgramManager::Current_Address = 0;

bool ProgramManager::IsJCallInstruction(const std::string& mnemonic)
{
	return JCallInstructions.count(mnemonic);
}


bool ProgramManager::IsExistingLabel(const std::string& expected_jump_point)
{
	return Labels.count(expected_jump_point);
}

//bool ProgramManager::CanRunFurther()
//{
//	if (Register::PC < (int)Program.size())
//	{
//		return true;
//	}
//	else
//	{
//		return Error::Throw(ERROR_TYPE::NEVER_REACHED_HLT);
//	}
//}

void ProgramManager::Clear()
{
	ProgramManager::Program.clear();
	ProgramManager::Labels.clear();
	ProgramManager::CallStack.clear();
	ProgramManager::HALT = false;
}



std::map<std::string, OpcodeInfo> ProgramManager::OP_INFO =
{
	{"ACI_DATA", {0xCE, 2}},
	{"ADC_A", {0x8F, 1}},
	{"ADC_B", {0x88, 1}},
	{"ADC_C", {0x89, 1}},
	{"ADC_D", {0x8A, 1}},
	{"ADC_E", {0x8B, 1}},
	{"ADC_H", {0x8C, 1}},
	{"ADC_L", {0x8D, 1}},
	{"ADC_M", {0x8E, 1}},
	{"ADD_A", {0x87, 1}},
	{"ADD_B", {0x80, 1}},
	{"ADD_C", {0x81, 1}},
	{"ADD_D", {0x82, 1}},
	{"ADD_E", {0x83, 1}},
	{"ADD_H", {0x84, 1}},
	{"ADD_L", {0x85, 1}},
	{"ADD_M", {0x86, 1}},
	{"ADI_DATA", {0xC6, 2}},
	{"ANA_A", {0xA7, 1}},
	{"ANA_B", {0xA0, 1}},
	{"ANA_C", {0xA1, 1}},
	{"ANA_D", {0xA2, 1}},
	{"ANA_E", {0xA3, 1}},
	{"ANA_H", {0xA4, 1}},
	{"ANA_L", {0xA5, 1}},
	{"ANA_M", {0xA6, 1}},
	{"ANI_DATA", {0xE6, 2}},
	{"CALL", {0xCD, 3}},
	{"CC", {0xDC, 3}},
	{"CM", {0xFC, 3}},
	{"CMA", {0x2F, 1}},
	{"CMC", {0x3F, 1}},
	{"CMP_A", {0xBF, 1}},
	{"CMP_B", {0xB8, 1}},
	{"CMP_C", {0xB9, 1}},
	{"CMP_D", {0xBA, 1}},
	{"CMP_E", {0xBB, 1}},
	{"CMP_H", {0xBC, 1}},
	{"CMP_L", {0xBD, 1}},
	{"CMP_M", {0xBD, 1}},
	{"CNC", {0xD4, 3}},
	{"CNZ", {0xC4, 3}},
	{"CP", {0xF4, 3}},
	{"CPE", {0xEC, 3}},
	{"CPI_DATA", {0xFE, 2}},
	{"CPO", {0xE4, 3}},
	{"CZ", {0xCC, 3}},
	{"DAA", {0x27, 1}},
	{"DAD_B", {0x09, 1}},
	{"DAD_D", {0x19, 1}},
	{"DAD_H", {0x29, 1}},
	{"DCR_A", {0x3D, 1}},
	{"DCR_B", {0x05, 1}},
	{"DCR_C", {0x0D, 1}},
	{"DCR_D", {0x15, 1}},
	{"DCR_E", {0x1D, 1}},
	{"DCR_H", {0x25, 1}},
	{"DCR_L", {0x2D, 1}},
	{"DCR_M", {0x35, 1}},
	{"DCX_B", {0x0B, 1}},
	{"DCX_D", {0x1B, 1}},
	{"DCX_H", {0x2B, 1}},
	{"HLT", {0x76, 1}},
	{"INR_A", {0x3C, 1}},
	{"INR_B", {0x04, 1}},
	{"INR_C", {0x0C, 1}},
	{"INR_D", {0x14, 1}},
	{"INR_E", {0x1C, 1}},
	{"INR_H", {0x24, 1}},
	{"INR_L", {0x2C, 1}},
	{"INR_M", {0x34, 1}},
	{"INX_B", {0x03, 1}},
	{"INX_D", {0x13, 1}},
	{"INX_H", {0x23, 1}},
	{"JC", {0xDA, 3}},
	{"JM", {0xFA, 3}},
	{"JMP", {0xC3, 3}},
	{"JNC", {0xD2, 3}},
	{"JNZ", {0xC2, 3}},
	{"JP", {0xF2, 3}},
	{"JPE", {0xEA, 3}},
	{"JPO", {0xE2, 3}},
	{"JZ", {0xCA, 3}},
	{"LDA_ADDRESS", {0x3A, 3}},
	{"LDAX_B", {0x0A, 1}},
	{"LDAX_D", {0x1A, 1}},
	{"LHLD_ADDRESS", {0x2A, 3}},
	{"LXI_B", {0x01, 3}},
	{"LXI_D", {0x11, 3}},
	{"LXI_H", {0x21, 3}},
	{"MOV_A_A", {0x7F, 1}},
	{"MOV_A_B", {0x78, 1}},
	{"MOV_A_C", {0x79, 1}},
	{"MOV_A_D", {0x7A, 1}},
	{"MOV_A_E", {0x7B, 1}},
	{"MOV_A_H", {0x7C, 1}},
	{"MOV_A_L", {0x7D, 1}},
	{"MOV_A_M", {0x7E, 1}},
	{"MOV_B_A", {0x47, 1}},
	{"MOV_B_B", {0x40, 1}},
	{"MOV_B_C", {0x41, 1}},
	{"MOV_B_D", {0x42, 1}},
	{"MOV_B_E", {0x43, 1}},
	{"MOV_B_H", {0x44, 1}},
	{"MOV_B_L", {0x45, 1}},
	{"MOV_B_M", {0x46, 1}},
	{"MOV_C_A", {0x4F, 1}},
	{"MOV_C_B", {0x48, 1}},
	{"MOV_C_C", {0x49, 1}},
	{"MOV_C_D", {0x4A, 1}},
	{"MOV_C_E", {0x4B, 1}},
	{"MOV_C_H", {0x4C, 1}},
	{"MOV_C_L", {0x4D, 1}},
	{"MOV_C_M", {0x4E, 1}},
	{"MOV_D_A", {0x57, 1}},
	{"MOV_D_B", {0x50, 1}},
	{"MOV_D_C", {0x51, 1}},
	{"MOV_D_D", {0x52, 1}},
	{"MOV_D_E", {0x53, 1}},
	{"MOV_D_H", {0x54, 1}},
	{"MOV_D_L", {0x55, 1}},
	{"MOV_D_M", {0x56, 1}},
	{"MOV_E_A", {0x5F, 1}},
	{"MOV_E_B", {0x58, 1}},
	{"MOV_E_C", {0x59, 1}},
	{"MOV_E_D", {0x5A, 1}},
	{"MOV_E_E", {0x5B, 1}},
	{"MOV_E_H", {0x5C, 1}},
	{"MOV_E_L", {0x5D, 1}},
	{"MOV_E_M", {0x5E, 1}},
	{"MOV_H_A", {0x67, 1}},
	{"MOV_H_B", {0x60, 1}},
	{"MOV_H_C", {0x61, 1}},
	{"MOV_H_D", {0x62, 1}},
	{"MOV_H_E", {0x63, 1}},
	{"MOV_H_H", {0x64, 1}},
	{"MOV_H_L", {0x65, 1}},
	{"MOV_H_M", {0x66, 1}},
	{"MOV_L_A", {0x6F, 1}},
	{"MOV_L_B", {0x68, 1}},
	{"MOV_L_C", {0x69, 1}},
	{"MOV_L_D", {0x6A, 1}},
	{"MOV_L_E", {0x6B, 1}},
	{"MOV_L_H", {0x6C, 1}},
	{"MOV_L_L", {0x6D, 1}},
	{"MOV_L_M", {0x6E, 1}},
	{"MOV_M_A", {0x77, 1}},
	{"MOV_M_B", {0x70, 1}},
	{"MOV_M_C", {0x71, 1}},
	{"MOV_M_D", {0x72, 1}},
	{"MOV_M_E", {0x73, 1}},
	{"MOV_M_H", {0x74, 1}},
	{"MOV_M_L", {0x75, 1}},
	{"MVI_A_DATA", {0x3E, 2}},
	{"MVI_B_DATA", {0x06, 2}},
	{"MVI_C_DATA", {0x0E, 2}},
	{"MVI_D_DATA", {0x16, 2}},
	{"MVI_E_DATA", {0x1E, 2}},
	{"MVI_H_DATA", {0x26, 2}},
	{"MVI_L_DATA", {0x2E, 2}},
	{"MVI_M_DATA", {0x36, 2}},
	{"NOP", {0x00, 1}},
	{"ORA_A", {0xB7, 1}},
	{"ORA_B", {0xB0, 1}},
	{"ORA_C", {0xB1, 1}},
	{"ORA_D", {0xB2, 1}},
	{"ORA_E", {0xB3, 1}},
	{"ORA_H", {0xB4, 1}},
	{"ORA_L", {0xB5, 1}},
	{"ORA_M", {0xB6, 1}},
	{"ORI_DATA", {0xF6, 2}},
	{"RAL", {0x17, 1}},
	{"RAR", {0x1F, 1}},
	{"RC", {0xD8, 1}},
	{"RET", {0xC9, 1}},
	{"RLC", {0x07, 1}},
	{"RM", {0xF8, 1}},
	{"RNC", {0xD0, 1}},
	{"RNZ", {0xC0, 1}},
	{"RP", {0xF0, 1}},
	{"RPE", {0xE8, 1}},
	{"RPO", {0xE0, 1}},
	{"RRC", {0x0F, 1}},
	{"RZ", {0xC8, 1}},
	{"SBB_A", {0x9F, 1}},
	{"SBB_B", {0x98, 1}},
	{"SBB_C", {0x99, 1}},
	{"SBB_D", {0x9A, 1}},
	{"SBB_E", {0x9B, 1}},
	{"SBB_H", {0x9C, 1}},
	{"SBB_L", {0x9D, 1}},
	{"SBB_M", {0x9E, 1}},
	{"SBI_DATA", {0xDE, 2}},
	{"SHLD_ADDRESS", {0x22, 3}},
	{"STA_ADDRESS", {0x32, 3}},
	{"STAX_B", {0x02, 1}},
	{"STAX_D", {0x12, 1}},
	{"STC", {0x37, 1}},
	{"SUB_A", {0x97, 1}},
	{"SUB_B", {0x90, 1}},
	{"SUB_C", {0x91, 1}},
	{"SUB_D", {0x92, 1}},
	{"SUB_E", {0x93, 1}},
	{"SUB_H", {0x94, 1}},
	{"SUB_L", {0x95, 1}},
	{"SUB_M", {0x96, 1}},
	{"SUI_DATA", {0xD6, 2}},
	{"XCHG", {0xEB, 1}},
	{"XRA_A", {0xAF, 1}},
	{"XRA_B", {0xA8, 1}},
	{"XRA_C", {0xA9, 1}},
	{"XRA_D", {0xAA, 1}},
	{"XRA_E", {0xAB, 1}},
	{"XRA_H", {0xAC, 1}},
	{"XRA_L", {0xAD, 1}},
	{"XRA_M", {0xAE, 1}},
	{"XRI_DATA", {0xEE, 2}},
};
void ProgramManager::LoadInstructionSet()
{
	Load[MNEMONIC::MVI] = MVI;
	Load[MNEMONIC::MOV] = MOV;
	Load[MNEMONIC::LDA] = LDA;
	Load[MNEMONIC::STA] = STA;
	Load[MNEMONIC::LHLD] = LHLD;
	Load[MNEMONIC::SHLD] = SHLD;
	Load[MNEMONIC::LXI] = LXI;
	Load[MNEMONIC::LDAX] = LDAX;
	Load[MNEMONIC::STAX] = STAX;
	Load[MNEMONIC::XCHG] = XCHG;
	Load[MNEMONIC::ADD] = ADD;
	Load[MNEMONIC::ADI] = ADI;
	Load[MNEMONIC::ADC] = ADC;
	Load[MNEMONIC::ACI] = ACI;
	Load[MNEMONIC::SUB] = SUB;
	Load[MNEMONIC::SBB] = SBB;
	Load[MNEMONIC::SUI] = SUI;
	Load[MNEMONIC::SBI] = SBI;
	Load[MNEMONIC::INR] = INR;
	Load[MNEMONIC::INX] = INX;
	Load[MNEMONIC::DCR] = DCR;
	Load[MNEMONIC::DCX] = DCX;
	Load[MNEMONIC::DAD] = DAD;
	Load[MNEMONIC::ANA] = ANA;
	Load[MNEMONIC::ANI] = ANI;
	Load[MNEMONIC::ORA] = ORA;
	Load[MNEMONIC::ORI] = ORI;
	Load[MNEMONIC::XRA] = XRA;
	Load[MNEMONIC::XRI] = XRI;
	Load[MNEMONIC::CMA] = CMA;
	Load[MNEMONIC::RLC] = RLC;
	Load[MNEMONIC::RAL] = RAL;
	Load[MNEMONIC::RRC] = RRC;
	Load[MNEMONIC::RAR] = RAR;
	Load[MNEMONIC::STC] = STC;
	Load[MNEMONIC::CMC] = CMC;
	Load[MNEMONIC::CMP] = CMP;
	Load[MNEMONIC::CPI] = CPI;
	Load[MNEMONIC::JMP] = JMP;
	Load[MNEMONIC::JC] = JC;
	Load[MNEMONIC::JNC] = JNC;
	Load[MNEMONIC::JZ] = JZ;
	Load[MNEMONIC::JNZ] = JNZ;
	Load[MNEMONIC::JPE] = JPE;
	Load[MNEMONIC::JPO] = JPO;
	Load[MNEMONIC::JM] = JM;
	Load[MNEMONIC::JP] = JP;
	Load[MNEMONIC::DAA] = DAA;
	Load[MNEMONIC::CALL] = CALL;
	Load[MNEMONIC::CNC] = CNC;
	Load[MNEMONIC::CC] = CC;
	Load[MNEMONIC::CNZ] = CNZ;
	Load[MNEMONIC::CZ] = CZ;
	Load[MNEMONIC::CPE] = CPE;
	Load[MNEMONIC::CPO] = CPO;
	Load[MNEMONIC::CP] = CP;
	Load[MNEMONIC::CM] = CM;
	Load[MNEMONIC::RET] = RET;
	Load[MNEMONIC::RNC] = RNC;
	Load[MNEMONIC::RC] = RC;
	Load[MNEMONIC::RNZ] = RNZ;
	Load[MNEMONIC::RZ] = RZ;
	Load[MNEMONIC::RPO] = RPO;
	Load[MNEMONIC::RPE] = RPE;
	Load[MNEMONIC::RP] = RP;
	Load[MNEMONIC::RM] = RM;
	Load[MNEMONIC::HLT] = HLT;
	Load[MNEMONIC::NOP] = NOP;

	//Loading Jump/Call Instruction
	JCallInstructions.insert(MNEMONIC::JMP);
	JCallInstructions.insert(MNEMONIC::JC);
	JCallInstructions.insert(MNEMONIC::JNC);
	JCallInstructions.insert(MNEMONIC::JZ);
	JCallInstructions.insert(MNEMONIC::JNZ);
	JCallInstructions.insert(MNEMONIC::JPE);
	JCallInstructions.insert(MNEMONIC::JPO);
	JCallInstructions.insert(MNEMONIC::JM);
	JCallInstructions.insert(MNEMONIC::JP);
	JCallInstructions.insert(MNEMONIC::CALL);
	JCallInstructions.insert(MNEMONIC::CNC);
	JCallInstructions.insert(MNEMONIC::CC);
	JCallInstructions.insert(MNEMONIC::CNZ);
	JCallInstructions.insert(MNEMONIC::CZ);
	JCallInstructions.insert(MNEMONIC::CPE);
	JCallInstructions.insert(MNEMONIC::CPO);
	JCallInstructions.insert(MNEMONIC::CP);
	JCallInstructions.insert(MNEMONIC::CM);

}


//Validator
bool Validator::IsValidLabel(const std::string& expected_label)
{
	std::string expected_mnemonic = expected_label;
	Converter::ToUpperString(expected_mnemonic); //Because mnemonic are stored in uppercase form.
	if (ProgramManager::IsValid(expected_mnemonic))//should not match any mnemonic
	{
		return false;
	}

	for (const char& x : expected_label)
	{
		if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9'))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}
//

bool ProgramManager::IsValid(const std::string& mnemonic)
{
	return Load.count(mnemonic);
}

bool ProgramManager::IsJCallInstruction(const std::string& mnemonic)
{
	return JCallInstructions.count(mnemonic);
}

bool ProgramManager::MOV(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 2))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string destination = operands.first, source = operands.second;

	if (destination == REGISTER::M && source == REGISTER::M)
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	bool OK = false;
	OK |= destination == REGISTER::M && Validator::IsValidRegister(source);
	OK |= source == REGISTER::M && Validator::IsValidRegister(destination);
	OK |= Validator::IsValidRegister(destination) && Validator::IsValidRegister(source);
	if (OK)
	{
		//MOV_R|M_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + destination + "_" + source];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}

	return true;
}

bool ProgramManager::MVI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 2))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}


	const std::string reg = operands.first;
	const std::string value = operands.second;

	if (!Validator::IsValidHex(value))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(value);

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//MVI_R|M_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}

	return true;
}

bool ProgramManager::LDA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	std::string address = operands.first;
	if (!Validator::IsValidHex(address))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}
	int nAddress = Converter::HexToDec(address);
	if (nAddress >= 0 && nAddress <= 0xffff)
	{
		//LDA_ADDRESS
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_ADDRESS"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nAddress & 0x00ff);
		MemoryManager::SetMemory(Current_Address + 2, (nAddress & 0xff00) >> 8);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_MEMORY_LOCATION, instruction.line_number);
	}
	return true;
}

bool ProgramManager::STA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	std::string address = operands.first;
	if (!Validator::IsValidHex(address))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}
	int nAddress = Converter::HexToDec(address);
	if (nAddress >= 0 && nAddress <= 0xffff)
	{
		//STA_ADDRESS
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_ADDRESS"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nAddress & 0x00ff);
		MemoryManager::SetMemory(Current_Address + 2, (nAddress & 0xff00) >> 8);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_MEMORY_LOCATION, instruction.line_number);
	}

	return true;
}

bool ProgramManager::LHLD(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	std::string address = operands.first;
	if (!Validator::IsValidHex(address))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}
	int nAddress = Converter::HexToDec(address);
	if (nAddress >= 0 && nAddress < 0xffff) // <0xffff as we also need a valid address + 1
	{
		//LHLD_ADDRESS
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_ADDRESS"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nAddress & 0x00ff);
		MemoryManager::SetMemory(Current_Address + 2, (nAddress & 0xff00) >> 8);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_MEMORY_LOCATION, instruction.line_number);
	}

	return true;
}

bool ProgramManager::SHLD(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	std::string address = operands.first;

	if (!Validator::IsValidHex(address))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nAddress = Converter::HexToDec(address);

	if (nAddress >= 0 && nAddress < 0xffff) // <0xffff as we also need a valid address + 1
	{
		//SHLD_ADDRESS
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_ADDRESS"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nAddress & 0x00ff);
		MemoryManager::SetMemory(Current_Address + 2, (nAddress & 0xff00) >> 8);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_MEMORY_LOCATION, instruction.line_number);
	}
	return true;
}



bool ProgramManager::LXI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 2))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;
	const std::string data = operands.second;

	if (!Validator::IsValidHex(data))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nData = Converter::HexToDec(data);

	if (nData < 0x0000 || nData > 0xffff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_16BIT_DATA, instruction.line_number);
	}

	bool OK = false;

	OK |= reg == REGISTER::B;
	OK |= reg == REGISTER::H;
	OK |= reg == REGISTER::D;

	if (OK)
	{
		//LXI_B|D|H
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nData & 0x00ff);
		MemoryManager::SetMemory(Current_Address + 2, (nData & 0xff00) >> 8);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER_PAIR, instruction.line_number);
	}
	return true;
}

bool ProgramManager::LDAX(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;

	OK |= reg == REGISTER::B;
	OK |= reg == REGISTER::D;
	//H register is not valid in LDAX

	if (OK)
	{
		//LDAX_B|D
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER_PAIR, instruction.line_number);
	}
	return true;
}

bool ProgramManager::STAX(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;
	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::B;
	OK |= reg == REGISTER::D;
	//H register is not valid in STAX

	if (OK)
	{
		//STAX_B|D
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER_PAIR, instruction.line_number);
	}
	return true;
}

bool ProgramManager::XCHG(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

//@Airthmatic Instrunction
bool ProgramManager::ADD(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//ADD_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::ADC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//ADC_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::ADI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	if (!Validator::IsValidHex(operands.first))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(operands.first);

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//ADI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::ACI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string data = operands.first;

	if (!Validator::IsValidHex(data))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(data);

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//ACI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::SUB(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;

	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//SUB_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}


bool ProgramManager::SBB(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//SBB_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return false;
}


bool ProgramManager::SUI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	if (!Validator::IsValidHex(operands.first))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(operands.first);

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//SUI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}
	return true;
}




bool ProgramManager::SBI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	if (!Validator::IsValidHex(operands.first))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(operands.first);
	int subtrahend = nValue;

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//SBI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}

	return true;
}


bool ProgramManager::DAA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//DAA
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;

	return true;
}

bool ProgramManager::INR(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//INR_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::INX(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::H;
	OK |= reg == REGISTER::D;
	OK |= reg == REGISTER::B;

	if (OK)
	{
		//INX_H|D|B
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::DCR(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//DCR_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::DCX(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::H;
	OK |= reg == REGISTER::D;
	OK |= reg == REGISTER::B;

	if (OK)
	{
		//DCX_H|D|B
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::DAD(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string Rp = operands.first;

	bool OK = false;
	OK |= Rp == REGISTER::H;
	OK |= Rp == REGISTER::D;
	OK |= Rp == REGISTER::B;

	if (OK)
	{
		//DAD_H|D|B
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + Rp];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::ANA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//ANA_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::ANI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	if (!Validator::IsValidHex(operands.first))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(operands.first);

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//ANI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}

	return true;

}

bool ProgramManager::ORA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);

	if (OK)
	{
		//ORA_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::ORI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	if (!Validator::IsValidHex(operands.first))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(operands.first);

	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//ORI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}

	return true;
}

bool ProgramManager::XRA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);
	if (OK)
	{
		//XRA_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}
	return true;
}

bool ProgramManager::XRI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	if (!Validator::IsValidHex(operands.first))
	{
		return Error::Throw(ERROR_TYPE::INVALID_HEX, instruction.line_number);
	}

	int nValue = Converter::HexToDec(operands.first);
	if (nValue < 0x00 || nValue > 0xff)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//XRI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, nValue);
		Current_Address += info.size;
	}

	return true;
}

bool ProgramManager::CMA(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//CMA
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RLC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//RLC
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RAL(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//RAL
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RRC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//RRC
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RAR(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//RAR
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::STC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//STC
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::CMC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	//CMC
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::CMP(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	const std::string reg = operands.first;

	bool OK = false;
	OK |= reg == REGISTER::M;
	OK |= Validator::IsValidRegister(reg);
	if (OK)
	{
		//CMP_R|M
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_" + reg];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		Current_Address += info.size;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_REGISTER, instruction.line_number);
	}

	return true;
}

bool ProgramManager::CPI(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}

	int R = Converter::HexToDec(operands.first);

	if (R < 0x00 || R > 0xFF)
	{
		return Error::Throw(ERROR_TYPE::EXPECTED_8BIT_DATA, instruction.line_number);
	}
	else
	{
		//CPI_DATA
		OpcodeInfo info = OP_INFO[instruction.mnemonic + "_DATA"];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		MemoryManager::SetMemory(Current_Address + 1, R);
		Current_Address += info.size;
	}

	return true;
}

bool ProgramManager::JMP(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, instruction.line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, instruction.line_number);
	}
	else
	{
		//JMP
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JC
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JNC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JNC
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JZ(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JZ
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JNZ(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JNZ
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JPE(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JPE
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JPO(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JPO
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JM(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JM
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::JP(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//JP
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::CALL(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CALL
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::CNC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CNC
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::CC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CC
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::CZ(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CZ
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::CNZ(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CNZ
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::CPE(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CPE
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::CPO(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CPO
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}


bool ProgramManager::CP(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CP
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::CM(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 1))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	else if (!ProgramManager::IsExistingLabel(operands.first))
	{
		return Error::Throw(ERROR_TYPE::NO_SUCH_LABEL, ProgramManager::Program[Register::PC].line_number);
	}
	else
	{
		//CM
		OpcodeInfo info = OP_INFO[instruction.mnemonic];
		MemoryManager::SetMemory(Current_Address, info.opcode);
		//Label Handling
		LabelPosition[operands.first].push_back(Current_Address + 1);
		Current_Address += info.size;
	}
	return true;
}

bool ProgramManager::RET(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	//RET
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RNC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RNC
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RC(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RC
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}
//
bool ProgramManager::RZ(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RZ
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RNZ(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RNZ
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}


bool ProgramManager::RPE(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RPE
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RPO(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	//RPO
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RM(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RM
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::RP(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}

	//RP
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::HLT(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	//HLT
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}

bool ProgramManager::NOP(const Instruction& instruction)
{
	const std::pair<std::string, std::string>& operands = instruction.operands;

	if (!Validator::ValidOperandCount(operands, 0))
	{
		return Error::Throw(ERROR_TYPE::INVALID_OPERANDS, ProgramManager::Program[Register::PC].line_number);
	}
	//NOP
	OpcodeInfo info = OP_INFO[instruction.mnemonic];
	MemoryManager::SetMemory(Current_Address, info.opcode);
	Current_Address += info.size;
	return true;
}
