// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Errrrorr lol lol!";
	}

	BitLen = len;
	MemLen = (len % 32 == 0) ? len / (sizeof(TELEM) * 8) : len / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
		throw "out of bounds exception";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] |  GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
		throw "out of bounds exception";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
		throw "out of bounds exception";
 return (pMem[GetMemIndex(n)] >> (n % (sizeof(TELEM) * 8))) & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	TBitField tmp(BitLen);
	if (BitLen != bf.GetLength())
		return 0;

	for (int i = 0; i < bf.MemLen; i++)
		if (this->pMem[i] != bf.pMem[i])
			return 0;

	return 1;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(1);
	if (bf.GetLength() > BitLen)
	{
		tmp = bf;
	}
	else
	{
		tmp = *this;
	}
	
	for (int i = 0; i < BitLen && i < bf.GetLength(); i++)
	{
		if(GetBit(i) | bf.GetBit(i)==1)
			tmp.SetBit(i);
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int max = bf.GetLength() >= BitLen ? bf.GetLength() : BitLen;
	TBitField tmp(max);
	for (int i = 0; i < BitLen && i < bf.GetLength(); i++)
	{
		if (GetBit(i) & bf.GetBit(i) == 1)
			tmp.SetBit(i);
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if(GetBit(i)==0)
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
