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
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] |  GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return (pMem[GetMemIndex(n)] >> (n % (sizeof(n) * 8))) & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField& TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen && i < bf.GetLength(); i++)
		tmp.SetBit(this->GetBit(i) | bf.GetBit(i));

	return tmp;
}

TBitField& TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen && i < bf.GetLength(); i++)
		tmp.SetBit(this->GetBit(i) & bf.GetBit(i));

	return tmp;
}

TBitField& TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.SetBit(~this->GetBit(i));

	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
