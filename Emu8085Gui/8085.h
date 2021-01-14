#include<fstream>
#include<sstream>
#include<set>
#include"constants.h"
#include"time_manager.h"
#include"validator.h"
#include"converter.h"
#include"memory_manager.h"
#include"registers.h"
#include"instruction.h"
#include"program_manager.h"

class Mnemonic
{
public:
	static std::map<std::string, bool (*)(const std::pair<std::string, std::string>&)> Execute;


	static void LoadInstructionSet();


	static bool IsValid(const std::string& mnemonic);


	static bool MOV(const std::pair<std::string, std::string>&);
	static bool MVI(const std::pair<std::string, std::string>&);
	static bool LDA(const std::pair<std::string, std::string>&);
	static bool STA(const std::pair<std::string, std::string>&);
	static bool LHLD(const std::pair<std::string, std::string>&);
	static bool SHLD(const std::pair<std::string, std::string>&);
	static bool LXI(const std::pair<std::string, std::string>&);
	static bool LDAX(const std::pair<std::string, std::string>&);
	static bool STAX(const std::pair<std::string, std::string>&);
	static bool XCHG(const std::pair<std::string, std::string>&);

	//@Airthmatic Instrunction
	static bool ADD(const std::pair<std::string, std::string>&);
	static bool ADC(const std::pair<std::string, std::string>&);
	static bool ADI(const std::pair<std::string, std::string>&);
	static bool ACI(const std::pair<std::string, std::string>&);
	static bool SUB(const std::pair<std::string, std::string>&);
	static bool SBB(const std::pair<std::string, std::string>&);//Not sure about flags
	static bool SUI(const std::pair<std::string, std::string>&);
	static bool SBI(const std::pair<std::string, std::string>&);
	static bool INR(const std::pair<std::string, std::string>&);//CY is not affected
	static bool INX(const std::pair<std::string, std::string>&);//No flags are affected during the execution
	static bool DCR(const std::pair<std::string, std::string>&);//CY is not affected
	static bool DCX(const std::pair<std::string, std::string>&);//No flags are affected during the execution
	static bool DAD(const std::pair<std::string, std::string>&);//only affect CY
	static bool DAA(const std::pair<std::string, std::string>&);

	//@Logical Instructions

	static bool ANA(const std::pair<std::string, std::string>&);
	static bool ANI(const std::pair<std::string, std::string>&);
	static bool ORA(const std::pair<std::string, std::string>&);
	static bool ORI(const std::pair<std::string, std::string>&);
	static bool XRA(const std::pair<std::string, std::string>&);
	static bool XRI(const std::pair<std::string, std::string>&);
	static bool CMA(const std::pair<std::string, std::string>&);//Flags are not affected by this instruction
	static bool RLC(const std::pair<std::string, std::string>&);
	static bool RAL(const std::pair<std::string, std::string>&);
	static bool RRC(const std::pair<std::string, std::string>&);
	static bool RAR(const std::pair<std::string, std::string>&);
	static bool STC(const std::pair<std::string, std::string>&);
	static bool CMC(const std::pair<std::string, std::string>&);
	static bool CMP(const std::pair<std::string, std::string>&);
	static bool CPI(const std::pair<std::string, std::string>&);

	//@Branching Instructions
	static bool JMP(const std::pair<std::string, std::string>&);
	static bool JC(const std::pair<std::string, std::string>&);
	static bool JNC(const std::pair<std::string, std::string>&);
	static bool JZ(const std::pair<std::string, std::string>&);
	static bool JNZ(const std::pair<std::string, std::string>&);
	static bool JPE(const std::pair<std::string, std::string>&);
	static bool JPO(const std::pair<std::string, std::string>&);
	static bool JM(const std::pair<std::string, std::string>&);
	static bool JP(const std::pair<std::string, std::string>&);

	//subroutine
	static bool CALL(const std::pair<std::string, std::string>&);
	static bool CNC(const std::pair<std::string, std::string>&);
	static bool CC(const std::pair<std::string, std::string>&);
	static bool CNZ(const std::pair<std::string, std::string>&);
	static bool CZ(const std::pair<std::string, std::string>&);
	static bool CPE(const std::pair<std::string, std::string>&);
	static bool CPO(const std::pair<std::string, std::string>&);
	static bool CP(const std::pair<std::string, std::string>&);
	static bool CM(const std::pair<std::string, std::string>&);
	static bool RET(const std::pair<std::string, std::string>&);
	static bool RNC(const std::pair<std::string, std::string>&);
	static bool RC(const std::pair<std::string, std::string>&);
	static bool RZ(const std::pair<std::string, std::string>&);
	static bool RNZ(const std::pair<std::string, std::string>&);
	static bool RPE(const std::pair<std::string, std::string>&);
	static bool RPO(const std::pair<std::string, std::string>&);
	static bool RP(const std::pair<std::string, std::string>&);
	static bool RM(const std::pair<std::string, std::string>&);

	//Other
	static bool HLT(const std::pair<std::string, std::string>&);
	static bool NOP(const std::pair<std::string, std::string>&);
};

std::map<std::string, bool (*)(const std::pair<std::string, std::string>&)> Mnemonic::Execute;

void Mnemonic::LoadInstructionSet()
{
	Execute[MNEMONIC::MVI] = MVI;
	Execute[MNEMONIC::MOV] = MOV;
	Execute[MNEMONIC::LDA] = LDA;
	Execute[MNEMONIC::STA] = STA;
	Execute[MNEMONIC::LHLD] = LHLD;
	Execute[MNEMONIC::SHLD] = SHLD;
	Execute[MNEMONIC::LXI] = LXI;
	Execute[MNEMONIC::LDAX] = LDAX;
	Execute[MNEMONIC::STAX] = STAX;
	Execute[MNEMONIC::XCHG] = XCHG;
	Execute[MNEMONIC::ADD] = ADD;
	Execute[MNEMONIC::ADI] = ADI;
	Execute[MNEMONIC::ADC] = ADC;
	Execute[MNEMONIC::ACI] = ACI;
	Execute[MNEMONIC::SUB] = SUB;
	Execute[MNEMONIC::SBB] = SBB;
	Execute[MNEMONIC::SUI] = SUI;
	Execute[MNEMONIC::SBI] = SBI;
	Execute[MNEMONIC::INR] = INR;
	Execute[MNEMONIC::INX] = INX;
	Execute[MNEMONIC::DCR] = DCR;
	Execute[MNEMONIC::DCX] = DCX;
	Execute[MNEMONIC::DAD] = DAD;
	Execute[MNEMONIC::ANA] = ANA;
	Execute[MNEMONIC::ANI] = ANI;
	Execute[MNEMONIC::ORA] = ORA;
	Execute[MNEMONIC::ORI] = ORI;
	Execute[MNEMONIC::XRA] = XRA;
	Execute[MNEMONIC::XRI] = XRI;
	Execute[MNEMONIC::CMA] = CMA;
	Execute[MNEMONIC::RLC] = RLC;
	Execute[MNEMONIC::RAL] = RAL;
	Execute[MNEMONIC::RRC] = RRC;
	Execute[MNEMONIC::RAR] = RAR;
	Execute[MNEMONIC::STC] = STC;
	Execute[MNEMONIC::CMC] = CMC;
	Execute[MNEMONIC::CMP] = CMP;
	Execute[MNEMONIC::CPI] = CPI;
	Execute[MNEMONIC::JMP] = JMP;
	Execute[MNEMONIC::JC] = JC;
	Execute[MNEMONIC::JNC] = JNC;
	Execute[MNEMONIC::JZ] = JZ;
	Execute[MNEMONIC::JNZ] = JNZ;
	Execute[MNEMONIC::JPE] = JPE;
	Execute[MNEMONIC::JPO] = JPO;
	Execute[MNEMONIC::JM] = JM;
	Execute[MNEMONIC::JP] = JP;
	Execute[MNEMONIC::DAA] = DAA;
	Execute[MNEMONIC::CALL] = CALL;
	Execute[MNEMONIC::CNC] = CNC;
	Execute[MNEMONIC::CC] = CC;
	Execute[MNEMONIC::CNZ] = CNZ;
	Execute[MNEMONIC::CZ] = CZ;
	Execute[MNEMONIC::CPE] = CPE;
	Execute[MNEMONIC::CPO] = CPO;
	Execute[MNEMONIC::CP] = CP;
	Execute[MNEMONIC::CM] = CM;
	Execute[MNEMONIC::RET] = RET;
	Execute[MNEMONIC::RNC] = RNC;
	Execute[MNEMONIC::RC] = RC;
	Execute[MNEMONIC::RNZ] = RNZ;
	Execute[MNEMONIC::RZ] = RZ;
	Execute[MNEMONIC::RPO] = RPO;
	Execute[MNEMONIC::RPE] = RPE;
	Execute[MNEMONIC::RP] = RP;
	Execute[MNEMONIC::RM] = RM;
	Execute[MNEMONIC::HLT] = HLT;
	Execute[MNEMONIC::NOP] = NOP;

}

//Validator
bool Validator::IsValidLabel(std::string expected_label)
{
	expected_label.erase(expected_label.end() - 1); // Erasing ':'

	std::string expected_mnemonic = expected_label;
	Converter::ToUpperString(expected_mnemonic); //Because mnemonic are stored in uppercase form.
	if (Mnemonic::IsValid(expected_mnemonic))//should not match any mnemonic
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


bool Mnemonic::IsValid(const std::string& mnemonic)
{
	return Execute.count(mnemonic);
}

bool Mnemonic::MOV(const std::pair<std::string, std::string>& operands)
{

	const std::string destination = operands.first, source = operands.second;

	if (destination == REGISTER::M)
	{
		MemoryManager::Memory[Register::HL()] = Register::Main[source];
	}
	else if (source == REGISTER::M)
	{
		Register::Main[destination] = MemoryManager::Memory[Register::HL()];
	}
	else
	{
		//Both will be registers
		Register::Main[destination] = Register::Main[source];
	}

	++Register::iPC;

	return ProgramManager::CanRunFurther();
}

bool Mnemonic::MVI(const std::pair<std::string, std::string>& operands)
{
	const std::string reg = operands.first;
	const std::string value = operands.second;

	int nValue = Converter::HexToDec(value);

	if (reg == REGISTER::M) //@Memory
	{
		MemoryManager::Memory[Register::HL()] = nValue;
	}
	else
	{
		//reg will be Register
		Register::Main[reg] = nValue;
	}
	++Register::iPC;

	return ProgramManager::CanRunFurther();
}

bool Mnemonic::LDA(const std::pair<std::string, std::string>& operands)
{
	std::string address = operands.first;

	int nAddress = Converter::HexToDec(address);

	Register::Main[REGISTER::A] = MemoryManager::Memory[nAddress];

	++Register::iPC;

	return ProgramManager::CanRunFurther();
}

bool Mnemonic::STA(const std::pair<std::string, std::string>& operands)
{

	std::string address = operands.first;

	int nAddress = Converter::HexToDec(address);

	MemoryManager::Memory[nAddress] = Register::Main[REGISTER::A];

	++Register::iPC;

	return ProgramManager::CanRunFurther();
}

bool Mnemonic::LHLD(const std::pair<std::string, std::string>& operands)
{
	std::string address = operands.first;

	int nAddress = Converter::HexToDec(address);

	Register::Main[REGISTER::L] = MemoryManager::Memory[nAddress];
	Register::Main[REGISTER::H] = MemoryManager::Memory[nAddress + 1];

	++Register::iPC;

	return ProgramManager::CanRunFurther();
}

bool Mnemonic::SHLD(const std::pair<std::string, std::string>& operands)
{

	std::string address = operands.first;

	int nAddress = Converter::HexToDec(address);

	MemoryManager::Memory[nAddress] = Register::Main[REGISTER::L];
	MemoryManager::Memory[nAddress + 1] = Register::Main[REGISTER::H];

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}



bool Mnemonic::LXI(const std::pair<std::string, std::string>& operands)
{

	const std::string reg = operands.first;

	const std::string data = operands.second;

	int nData = Converter::HexToDec(data);

	if (reg == REGISTER::B)
	{
		Register::Main[REGISTER::B] = (nData & 0xff00) >> 8;
		Register::Main[REGISTER::C] = nData & 0x00ff;
	}
	else if (reg == REGISTER::H)
	{
		Register::Main[REGISTER::H] = (nData & 0xff00) >> 8;
		Register::Main[REGISTER::L] = nData & 0x00ff;
	}
	else if(reg == REGISTER::D)
	{
		
		Register::Main[REGISTER::D] = (nData & 0xff00) >> 8;
		Register::Main[REGISTER::E] = nData & 0x00ff;
	}
	else//reg == REGISTER::SP
	{
		Register::SP = nData;
	}

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::LDAX(const std::pair<std::string, std::string>& operands)
{

	const std::string reg = operands.first;

	if (reg == REGISTER::B)
	{
		Register::Main[REGISTER::A] = MemoryManager::Memory[Register::BC()];
	}
	else
	{
		//reg == D
		Register::Main[REGISTER::A] = MemoryManager::Memory[Register::DE()];
	}

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::STAX(const std::pair<std::string, std::string>& operands)
{
	const std::string reg = operands.first;

	if (reg == REGISTER::B)
	{
		MemoryManager::Memory[Register::BC()] = Register::Main[REGISTER::A];
	}
	else
	{
		//reg == D
		MemoryManager::Memory[Register::DE()] = Register::Main[REGISTER::A];
	}
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::XCHG(const std::pair<std::string, std::string>& operands)
{
	std::swap(Register::Main[REGISTER::H], Register::Main[REGISTER::D]);
	std::swap(Register::Main[REGISTER::L], Register::Main[REGISTER::E]);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

//@Airthmatic Instrunction
bool Mnemonic::ADD(const std::pair<std::string, std::string>& operands)
{
	const std::string reg = operands.first;

	int LSN_A = Register::Main[REGISTER::A] & 0x0f, LSN_R = 0;//LSN: Least singnificant nibble

	if (reg == REGISTER::M)
	{
		LSN_R = MemoryManager::Memory[Register::HL()] & 0x0f;
		Register::Main[REGISTER::A] += MemoryManager::Memory[Register::HL()];

	}
	else
	{
		//reg will be a register
		LSN_R = Register::Main[reg] & 0x0f;
		Register::Main[REGISTER::A] += Register::Main[reg];
	}

	Register::UpdateFlags(LSN_A + LSN_R);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::ADC(const std::pair<std::string, std::string>& operands)
{
	const std::string reg = operands.first;

	int LSN_A = Register::Main[REGISTER::A] & 0x0f, LSN_R = 0;

	if (reg == REGISTER::M)
	{
		LSN_R = MemoryManager::Memory[Register::HL()] & 0x0f;
		Register::Main[REGISTER::A] += MemoryManager::Memory[Register::HL()] + Register::Flag::CY;

	}
	else
	{
		//reg will be a register
		LSN_R = Register::Main[reg] & 0x0f;
		Register::Main[REGISTER::A] += Register::Main[reg] + Register::Flag::CY;
	}

	Register::UpdateFlags(LSN_A + LSN_R);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::ADI(const std::pair<std::string, std::string>& operands)
{


	int nValue = Converter::HexToDec(operands.first);
	int LSN_A = Register::Main[REGISTER::A] & 0x0f;
	int LSN_R = nValue & 0x0f;

	Register::Main[REGISTER::A] += nValue;

	Register::UpdateFlags(LSN_A + LSN_R);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::ACI(const std::pair<std::string, std::string>& operands)
{
	std::string data = operands.first;

	int nValue = Converter::HexToDec(data);
	int LSN_A = Register::Main[REGISTER::A] & 0x0f;
	int LSN_R = nValue & 0x0f;

	Register::Main[REGISTER::A] += nValue + Register::Flag::CY;

	Register::UpdateFlags(LSN_A + LSN_R);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}


//For subtraction check carry separately which will work as follows: Register::Flag::CY = subtrahend > minuend (carry will not be included)
bool Mnemonic::SUB(const std::pair<std::string, std::string>& operands)
{

	const std::string reg = operands.first;

	int LSN_A = Register::Main[REGISTER::A] & 0x0f, LSN_R = 0, minuend = Register::Main[REGISTER::A], subtrahend = 0;

	if (reg == REGISTER::M)
	{
		subtrahend = MemoryManager::Memory[Register::HL()];

		int _2sc = Utility::_8bit_2sc(MemoryManager::Memory[Register::HL()]);
		LSN_R = _2sc & 0x0f;
		Register::Main[REGISTER::A] += _2sc;
	}
	else
	{
		// reg will be a register
		subtrahend = Register::Main[reg];
		int _2sc = Utility::_8bit_2sc(Register::Main[reg]);
		LSN_R = _2sc & 0x0f;
		Register::Main[REGISTER::A] += _2sc;
	}
	//@Setting carry flag explicitly
	Register::Flag::CY = subtrahend > minuend;
	Register::UpdateFlags(LSN_A + LSN_R, true);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::SBB(const std::pair<std::string, std::string>& operands)
{

	const std::string reg = operands.first;

	int LSN_A = Register::Main[REGISTER::A] & 0x0f, LSN_R = 0, minuend = Register::Main[REGISTER::A], subtrahend = 0;
	//int _4Bit_C = Register::Flag::CY ? 0xF : 0x0; // Not sure if last nibble of Carry is also responsible for AC
	if (reg == REGISTER::M)
	{
		subtrahend = MemoryManager::Memory[Register::HL()];

		int _2sc = Utility::_8bit_2sc(MemoryManager::Memory[Register::HL()]);
		LSN_R = _2sc & 0x0f;
		Register::Main[REGISTER::A] += _2sc + Utility::_8bit_2sc(Register::Flag::CY);

	}
	else
	{
		//reg will be a register
		subtrahend = Register::Main[reg];
		int _2sc = Utility::_8bit_2sc(Register::Main[reg]);
		LSN_R = _2sc & 0x0f;
		Register::Main[REGISTER::A] += _2sc + Utility::_8bit_2sc(Register::Flag::CY);
	}

	Register::Flag::CY = subtrahend > minuend;
	Register::UpdateFlags(LSN_A + LSN_R, true); //Add _4Bit_C if last nibble of Carry is also responsible for AC
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::SUI(const std::pair<std::string, std::string>& operands)
{

	int nValue = Converter::HexToDec(operands.first), minuend = Register::Main[REGISTER::A];
	int subtrahend = nValue;


	int _2sc = Utility::_8bit_2sc(nValue);
	int LSN_A = Register::Main[REGISTER::A] & 0x0f;
	int LSN_R = _2sc & 0x0f;
	Register::Main[REGISTER::A] += _2sc;

	Register::Flag::CY = subtrahend > minuend;
	Register::UpdateFlags(LSN_A + LSN_R, true);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::SBI(const std::pair<std::string, std::string>& operands)
{

	int nValue = Converter::HexToDec(operands.first), minuend = Register::Main[REGISTER::A];
	int subtrahend = nValue;

	int _2sc = Utility::_8bit_2sc(nValue);
	int LSN_A = Register::Main[REGISTER::A] & 0x0f;
	int LSN_R = _2sc & 0x0f;
	//_4Bit_C = Register::Flag::CY ? 0xF : 0x0;// Not sure if last nibble of Carry is also responsible for AC
	Register::Main[REGISTER::A] += _2sc + Utility::_8bit_2sc(Register::Flag::CY);//Add _4Bit_C if last nibble of Carry is also responsible for AC

	Register::Flag::CY = subtrahend > minuend;
	Register::UpdateFlags(LSN_A + LSN_R, true);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::DAA(const std::pair<std::string, std::string>& operands)
{

	int LSN = Register::Main[REGISTER::A] & 0x0f;
	int MSN = (Register::Main[REGISTER::A] & 0xf0) >> 4;

	if ((LSN > 9 || Register::Flag::AC) && (MSN > 9 || Register::Flag::CY))
	{
		Register::Main[REGISTER::A] += 0x66;
		Register::Flag::CY = true;
		Register::Flag::AC = true;
	}
	else if (LSN > 9 || Register::Flag::AC)
	{
		Register::Main[REGISTER::A] += 0x06;
		Register::Flag::AC = true;
	}
	else if (MSN > 9 || Register::Flag::CY)
	{
		Register::Main[REGISTER::A] += 0x60;
		Register::Flag::CY = true;
	}

	Utility::_8Bit_Normalization(Register::Main[REGISTER::A]);

	Register::Flag::SF = Register::Main[REGISTER::A] & (1 << 7); //@Sign Flag

	Register::Flag::ZF = Register::Main[REGISTER::A] == 0; //@Zero Flag

	Register::Flag::PF = !(Utility::_set_bits_count(Register::Main[REGISTER::A]) & 1); //@Pairty Flag

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::INR(const std::pair<std::string, std::string>& operands)//CY is not affected
{

	const std::string reg = operands.first;

	if (reg == REGISTER::M)
	{
		int nValue = MemoryManager::Memory[Register::HL()];
		Register::Flag::AC = ((nValue & 0x0f) + 0x01) > 0x0f;//@Auxiliary carry
		++MemoryManager::Memory[Register::HL()];
		Utility::_8Bit_Normalization(MemoryManager::Memory[Register::HL()]);
		Register::Flag::PF = !(Utility::_set_bits_count(MemoryManager::Memory[Register::HL()]) & 1);//@Parity Flag
		Register::Flag::SF = MemoryManager::Memory[Register::HL()] & (1 << 7);//Sign Flag
		Register::Flag::ZF = MemoryManager::Memory[Register::HL()] == 0;//Zero Flag
	}
	else
	{
		//reg will be a register
		int nValue = Register::Main[reg];
		Register::Flag::AC = ((nValue & 0x0f) + 0x01) > 0x0f;//@Auxiliary carry
		++Register::Main[reg];
		Utility::_8Bit_Normalization(Register::Main[reg]);
		Register::Flag::PF = !(Utility::_set_bits_count(Register::Main[reg]) & 1);//@Parity Flag
		Register::Flag::SF = Register::Main[reg] & (1 << 7);//Sign Flag
		Register::Flag::ZF = Register::Main[reg] == 0;//Zero Flag
	}
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::INX(const std::pair<std::string, std::string>& operands)//No flags are affected during the execution
{

	const std::string reg = operands.first;

	if (reg == REGISTER::H)
	{
		int DATA = Register::HL();
		++DATA;
		Utility::_16Bit_Normalization(DATA);

		Register::Main[REGISTER::H] = (DATA & 0xff00) >> 8;
		Register::Main[REGISTER::L] = DATA & 0x00ff;
	}
	else if (reg == REGISTER::D)
	{
		int DATA = Register::DE();
		++DATA;
		Utility::_16Bit_Normalization(DATA);
		Register::Main[REGISTER::D] = (DATA & 0xff00) >> 8;
		Register::Main[REGISTER::E] = DATA & 0x00ff;
	}
	else
	{
		//reg will be B
		int DATA = Register::BC();
		++DATA;
		Utility::_16Bit_Normalization(DATA);
		Register::Main[REGISTER::B] = (DATA & 0xff00) >> 8;
		Register::Main[REGISTER::C] = DATA & 0x00ff;
	}

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::DCR(const std::pair<std::string, std::string>& operands)//CY is not affected
{

	const std::string reg = operands.first;

	if (reg == REGISTER::M)
	{
		int nValue = MemoryManager::Memory[Register::HL()];
		Register::Flag::AC = (nValue & 0x0f) + 0x0f > 0x0f;
		--MemoryManager::Memory[Register::HL()];
		Utility::_8Bit_Normalization(MemoryManager::Memory[Register::HL()]);
		Register::Flag::PF = !(Utility::_set_bits_count(MemoryManager::Memory[Register::HL()]) & 1);//@Parity Flag
		Register::Flag::SF = MemoryManager::Memory[Register::HL()] & (1 << 7);//Sign Flag
		Register::Flag::ZF = MemoryManager::Memory[Register::HL()] == 0;//Zero Flag
	}
	else
	{
		// reg will be a register
		int nValue = Register::Main[reg];
		Register::Flag::AC = (nValue & 0x0f) + 0x0f > 0x0f;;//@Not sure about auxiliary flag
		--Register::Main[reg];
		Utility::_8Bit_Normalization(Register::Main[reg]);
		Register::Flag::PF = !(Utility::_set_bits_count(Register::Main[reg]) & 1);//@Parity Flag
		Register::Flag::SF = Register::Main[reg] & (1 << 7);//Sign Flag
		Register::Flag::ZF = Register::Main[reg] == 0;//Zero Flag
	}

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::DCX(const std::pair<std::string, std::string>& operands)//No flags are affected during the execution
{

	const std::string reg = operands.first;

	if (reg == REGISTER::H)
	{
		int DATA = Register::HL();
		--DATA;
		Utility::_16Bit_Normalization(DATA);
		Register::Main[REGISTER::H] = (DATA & 0xff00) >> 8;
		Register::Main[REGISTER::L] = DATA & 0x00ff;
	}
	else if (reg == REGISTER::D)
	{
		int DATA = Register::DE();
		--DATA;
		Utility::_16Bit_Normalization(DATA);
		Register::Main[REGISTER::D] = (DATA & 0xff00) >> 8;
		Register::Main[REGISTER::E] = DATA & 0x00ff;
	}
	else
	{
		//reg will be B
		int DATA = Register::BC();
		--DATA;
		Utility::_16Bit_Normalization(DATA);
		Register::Main[REGISTER::B] = (DATA & 0xff00) >> 8;
		Register::Main[REGISTER::C] = DATA & 0x00ff;
	}

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::DAD(const std::pair<std::string, std::string>& operands)//only affect CY
{
	const std::string Rp = operands.first;
	int HL_DATA = Register::HL(), Rp_DATA = 0;
	if (Rp == REGISTER::H)
	{
		Rp_DATA = Register::HL();
	}
	else if (Rp == REGISTER::D)
	{
		Rp_DATA = Register::DE();
	}
	else
	{
		//Rp will be B
		Rp_DATA = Register::BC();
	}

	HL_DATA += Rp_DATA;
	Register::Flag::CY = HL_DATA & (1 << 16);//@Checking for Carry
	Utility::_16Bit_Normalization(HL_DATA);
	std::string xDATA = Converter::DecToHex(HL_DATA, 16);
	Register::Main[REGISTER::H] = Converter::HexToDec(xDATA.substr(0, 2));
	Register::Main[REGISTER::L] = Converter::HexToDec(xDATA.substr(2, 2));
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

//@Logical Instructions
bool Mnemonic::ANA(const std::pair<std::string, std::string>& operands)
{

	const std::string reg = operands.first;

	if (reg == REGISTER::M)
	{
		Register::Main[REGISTER::A] &= MemoryManager::Memory[Register::HL()];
	}
	else
	{
		//reg will be a Register
		Register::Main[REGISTER::A] &= Register::Main[reg];
	}

	Register::UpdateFlags(16);//16: As after executing AND instruction AC flag become set
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::ANI(const std::pair<std::string, std::string>& operands)
{
	int nValue = Converter::HexToDec(operands.first);

	Register::Main[REGISTER::A] &= nValue;

	Register::UpdateFlags(16);//16: As after executing AND instruction AC flag become set
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::ORA(const std::pair<std::string, std::string>& operands)
{
	const std::string reg = operands.first;
	if (reg == REGISTER::M)
	{
		Register::Main[REGISTER::A] |= MemoryManager::Memory[Register::HL()];
	}
	else
	{
		//reg will be a register
		Register::Main[REGISTER::A] |= Register::Main[reg];
	}

	Register::UpdateFlags(1);//1: As there can not be any auxiliary carry during bitwise operation
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::ORI(const std::pair<std::string, std::string>& operands)
{
	int nValue = Converter::HexToDec(operands.first);

	Register::Main[REGISTER::A] |= nValue;

	Register::UpdateFlags(1);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::XRA(const std::pair<std::string, std::string>& operands)
{

	const std::string reg = operands.first;
	if (reg == REGISTER::M)
	{
		Register::Main[REGISTER::A] ^= MemoryManager::Memory[Register::HL()];
	}
	else
	{
		//reg will be a register
		Register::Main[REGISTER::A] ^= Register::Main[reg];
	}

	Register::UpdateFlags(1);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::XRI(const std::pair<std::string, std::string>& operands)
{
	int nValue = Converter::HexToDec(operands.first);
	Register::Main[REGISTER::A] ^= nValue;
	Register::UpdateFlags(1);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CMA(const std::pair<std::string, std::string>& operands)//Flags are not affected by this instruction
{
	for (int i = 0; i < 8; ++i)
	{
		Register::Main[REGISTER::A] ^= (1 << i);
	}
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RLC(const std::pair<std::string, std::string>& operands)
{
	Register::Flag::CY = Register::Main[REGISTER::A] & (1 << 7);
	Register::Main[REGISTER::A] <<= 1; //Left Shift by 1 bit
	Register::Main[REGISTER::A] |= Register::Flag::CY ? 1 : 0;
	Utility::_8Bit_Normalization(Register::Main[REGISTER::A]);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RAL(const std::pair<std::string, std::string>& operands)
{
	bool MSB = Register::Main[REGISTER::A] & (1 << 7);
	Register::Main[REGISTER::A] <<= 1;//Left Shift by 1 bit
	Register::Main[REGISTER::A] |= Register::Flag::CY ? 1 : 0;
	Register::Flag::CY = MSB;
	Utility::_8Bit_Normalization(Register::Main[REGISTER::A]);
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RRC(const std::pair<std::string, std::string>& operands)
{
	Register::Flag::CY = Register::Main[REGISTER::A] & 1;
	Register::Main[REGISTER::A] >>= 1; //Right Shift by 1 bit
	Register::Main[REGISTER::A] |= Register::Flag::CY ? (1 << 7) : 0;
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RAR(const std::pair<std::string, std::string>& operands)
{

	bool LSB = Register::Main[REGISTER::A] & 1;
	Register::Main[REGISTER::A] >>= 1;//Right Shift by 1 bit
	Register::Main[REGISTER::A] |= Register::Flag::CY ? (1 << 7) : 0;
	Register::Flag::CY = LSB;
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::STC(const std::pair<std::string, std::string>& operands)
{
	Register::Flag::CY = 1;
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CMC(const std::pair<std::string, std::string>& operands)
{
	Register::Flag::CY = !Register::Flag::CY;
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CMP(const std::pair<std::string, std::string>& operands)
{
	const std::string reg = operands.first;
	int A = Register::Main[REGISTER::A], R = 0;
	if (reg == REGISTER::M)
	{
		R = MemoryManager::Memory[Register::HL()];
	}
	else
	{
		//reg will be a register
		R = Register::Main[reg];
	}

	int _2sc = Utility::_8bit_2sc(R);
	int temp = A + _2sc;
	Utility::_8Bit_Normalization(temp);
	Register::Flag::PF = !(Utility::_set_bits_count(temp) & 1);

	int LSN_A = A & 0x0f;
	int LSN_R = _2sc & 0x0f;

	Register::Flag::AC = LSN_A + LSN_R > 0xf;

	Register::Flag::CY = A < R;
	Register::Flag::SF = A < R;
	Register::Flag::ZF = A == R;

	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CPI(const std::pair<std::string, std::string>& operands)
{
	int A = Register::Main[REGISTER::A], DATA = Converter::HexToDec(operands.first);


	int _2sc = Utility::_8bit_2sc(DATA);
	int temp = A + _2sc;
	Utility::_8Bit_Normalization(temp);
	Register::Flag::PF = !(Utility::_set_bits_count(temp) & 1);

	int LSN_A = A & 0x0f;
	int LSN_R = _2sc & 0x0f;
	Register::Flag::AC = LSN_A + LSN_R > 0xf;

	Register::Flag::CY = A < DATA;
	Register::Flag::SF = A < DATA;
	Register::Flag::ZF = A == DATA;
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

//@Branching Instructions
bool Mnemonic::JMP(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = ProgramManager::iLabels[operands.first];
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JC(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::CY ? ProgramManager::iLabels[operands.first] : Register::iPC + 1;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JNC(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::CY ? Register::iPC + 1 : ProgramManager::iLabels[operands.first];
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JZ(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::ZF ? ProgramManager::iLabels[operands.first] : Register::iPC + 1;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JNZ(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::ZF ? Register::iPC + 1 : ProgramManager::iLabels[operands.first];
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JPE(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::PF ? ProgramManager::iLabels[operands.first] : Register::iPC + 1;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JPO(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::PF ? Register::iPC + 1 : ProgramManager::iLabels[operands.first];
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JM(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::SF ? ProgramManager::iLabels[operands.first] : Register::iPC + 1;
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::JP(const std::pair<std::string, std::string>& operands)
{
	Register::iPC = Register::Flag::SF ? Register::iPC + 1 : ProgramManager::iLabels[operands.first];
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CALL(const std::pair<std::string, std::string>& operands)
{
	ProgramManager::CallStack.push_back(Register::iPC + 1);
	Register::iPC = ProgramManager::iLabels[operands.first];
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::CNC(const std::pair<std::string, std::string>& operands)
{
	if (Register::Flag::CY)
	{
		++Register::iPC;
	}
	else
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CC(const std::pair<std::string, std::string>& operands)
{
	if (Register::Flag::CY)
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::CZ(const std::pair<std::string, std::string>& operands)
{


	if (Register::Flag::ZF)
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::CNZ(const std::pair<std::string, std::string>& operands)
{

	if (Register::Flag::CY)
	{
		++Register::iPC;
	}
	else
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::CPE(const std::pair<std::string, std::string>& operands)
{

	if (Register::Flag::PF)
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	else
	{
		++Register::iPC;
	}

	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CPO(const std::pair<std::string, std::string>& operands)
{

	if (Register::Flag::PF)
	{
		++Register::iPC;
	}
	else
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::CP(const std::pair<std::string, std::string>& operands)
{

	if (Register::Flag::SF)
	{
		++Register::iPC;
	}
	else
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::CM(const std::pair<std::string, std::string>& operands)
{
	if (Register::Flag::SF)
	{
		ProgramManager::CallStack.push_back(Register::iPC + 1);
		Register::iPC = ProgramManager::iLabels[operands.first];
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RET(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	Register::iPC = ProgramManager::CallStack.back();
	ProgramManager::CallStack.pop_back();
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RNC(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::CY)
	{
		++Register::iPC;
	}
	else
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RC(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::CY)
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RZ(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::ZF)
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RNZ(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::ZF)
	{
		++Register::iPC;
	}
	else
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	return ProgramManager::CanRunFurther();
}


bool Mnemonic::RPE(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::PF)
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RPO(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::PF)
	{
		++Register::iPC;
	}
	else
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RM(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::SF)
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	else
	{
		++Register::iPC;
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::RP(const std::pair<std::string, std::string>& operands)
{
	if (ProgramManager::CallStack.empty())//There can't be a return instruction if we don't have any address to return. 
	{
		return Error::Throw(ERROR_TYPE::RETURN_WITHOUT_CALL);
	}

	if (Register::Flag::SF)
	{
		++Register::iPC;
	}
	else
	{
		Register::iPC = ProgramManager::CallStack.back();
		ProgramManager::CallStack.pop_back();
	}
	return ProgramManager::CanRunFurther();
}

bool Mnemonic::HLT(const std::pair<std::string, std::string>& operands)//return false even on successful execcution But will change Program::HLT = true
{
	ProgramManager::HALT = true;
	Register::PC = ProgramManager::Program[Register::iPC].loading_address + 0x0001;
	Utility::_16Bit_Normalization(Register::PC);
	return false;
}

bool Mnemonic::NOP(const std::pair<std::string, std::string>& operands)
{
	++Register::iPC;
	return ProgramManager::CanRunFurther();
}

//Function to print the lexer output to a file
void DebugLex()
{
	std::ofstream file;
	file.open("debug_lex.txt");
	for (const Instruction& s : ProgramManager::Program)
	{
		file << s.label << ' ' << s.mnemonic << ' ' << s.operands.first << ' ' << s.operands.second << '\n';
	}
}


bool ProgramManager::Read(const std::string filePath)
{
	//Resetting
	ProgramManager::Clear();
	Register::Clear();

	std::fstream file;
	file.open(filePath, std::ios::in);
	int line_number = 1;
	while (!file.eof())
	{
		std::string currentLine;
		std::getline(file, currentLine);

		//Checking for commented line and empty line
		if (currentLine.empty() || currentLine.front() == '@')
		{
			++line_number;
			continue;
		}

		std::string token;
		std::vector<std::string> vTokens;
		Instruction instruction;
		instruction.line_number = line_number;

		//Tokenization
		for (const char& x : currentLine)
		{
			if (x == ' ' || x == '\t')
			{
				if (!token.empty())
				{
					vTokens.push_back(token);
					token.clear();
				}
			}
			else if (x == ',')
			{
				if (!token.empty())
				{
					vTokens.push_back(token);
					token.clear();
				}
				vTokens.push_back(",");
			}
			else if (x == ':')
			{
				if (token.empty())
				{
					return Error::Throw(ERROR_TYPE::SYNTAX);
				}
				token.push_back(x);
				vTokens.push_back(token);
				token.clear();
			}
			else
			{
				token.push_back(x);
			}
		}
		if (!token.empty())
		{
			vTokens.push_back(token);
			token.clear();
		}

		if (vTokens.empty())//All white spaces => Ignore this line
		{
			++line_number;
			continue;
		}

		int nTokenIndex = 0, nTotalTokens = vTokens.size();
		if (nTotalTokens > 5)//we can have at max 5 token in a line
		{
			return Error::Throw(ERROR_TYPE::SYNTAX);
		}
		//First Token may be a Label
		if (vTokens[nTokenIndex].back() == ':')
		{
			std::string& s = vTokens[nTokenIndex];
			if (Validator::IsValidLabel(s))
			{
				instruction.label = s.substr(0, s.size() - 1);
				ProgramManager::iLabels[instruction.label] = Program.size();
				++nTokenIndex;
			}
			else
			{
				//error as string containg ':' as suffix must be label only
				return Error::Throw(ERROR_TYPE::INVALID_LABEL, line_number);
			}
		}

		//Checking for mnemonic
		if (nTokenIndex < nTotalTokens)
		{
			std::string& s = vTokens[nTokenIndex];
			Converter::ToUpperString(s);
			if (Mnemonic::IsValid(s))
			{
				instruction.mnemonic = s;
				++nTokenIndex;
			}
			else
			{
				return Error::Throw(ERROR_TYPE::INVALID_MNEMONIC, line_number);
			}
		}
		else
		{
			//This token should have to be a mnemonic
			return Error::Throw(ERROR_TYPE::SYNTAX, line_number);
		}

		//First operand
		if (nTokenIndex < nTotalTokens)
		{
			std::string& s = vTokens[nTokenIndex];
			/*First operand can be a label.
			So we don't have to change it into upper case form as labels are case sensitive.*/
			if (!ProgramManager::IsJCallInstruction(instruction.mnemonic))
			{
				Converter::ToUpperString(s);
			}

			instruction.operands.first = s;
			++nTokenIndex;
		}

		/*If there are two operands then there should be a ',' in between.*/
		bool bComma = false;
		if (nTokenIndex < nTotalTokens)
		{
			std::string& s = vTokens[nTokenIndex];
			if (s == ",")
			{
				bComma = true;
				++nTokenIndex;
			}
			else
			{
				return Error::Throw(ERROR_TYPE::SYNTAX);
			}
		}

		//Second Operand
		if (nTokenIndex < nTotalTokens)
		{
			std::string &s  = vTokens[nTokenIndex];
			Converter::ToUpperString(s);
			instruction.operands.second = s;
			++nTokenIndex;
		}
		else if(bComma)
		{
			//There must be an opeands after comma
			return Error::Throw(ERROR_TYPE::SYNTAX);
		}

		if (nTokenIndex < nTotalTokens) //If there are still token left (after second operands), it must be a syntax error
		{
			return Error::Throw(ERROR_TYPE::SYNTAX);
		}
		Program.push_back(instruction);
		++line_number;
	}

	if (Program.empty())
	{
		return Error::Throw(ERROR_TYPE::EMPTY_FILE);
	}
	else
	{
		return true;
	}
}




void ProgramManager::Run()
{
	TimeManager::Reset();
	while (Mnemonic::Execute[Program[Register::iPC].mnemonic](Program[Register::iPC].operands))
	{
		if (TimeManager::TLE())
		{
			Error::Throw(ERROR_TYPE::INFINITE_LOOP_OR_RECURSIVE_CALL);
			break;
		}
	}
}

bool ProgramManager::LoadProgramInMemory(const std::string& filePath, int loadingLocation)
{
	
	if (!ProgramManager::Read(filePath))
	{
		return false;
	}

	ProgramManager::CurrentLoadingLocation = loadingLocation;//Address from where loading will takeplace

	for (Instruction& instruction : ProgramManager::Program)
	{
		if (ProgramManager::Load[instruction.mnemonic](instruction))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	//Loading label Address
	ProgramManager::LoadLabelAddress();
	Register::PC = loadingLocation; //If every thing is loaded perfectly update program counter to the address of first instruction 
	return true;
}