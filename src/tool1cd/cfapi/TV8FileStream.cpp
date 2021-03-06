/*
    Tool1CD library provides access to 1CD database files.
    Copyright © 2009-2017 awa
    Copyright © 2017-2018 E8 Tools contributors

    This file is part of Tool1CD Library.

    Tool1CD Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tool1CD Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Tool1CD Library.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "TV8FileStream.h"

using namespace System;

TV8FileStream::TV8FileStream(V8File* f, bool ownfile) : TStream(), file(f), own(ownfile)
{
	pos = 0l;
	file->streams().insert(this);
}

//---------------------------------------------------------------------------
// декструктор
TV8FileStream::~TV8FileStream()
{
	if(own) delete file;
	else file->streams().erase(this);
}

//---------------------------------------------------------------------------
// чтение буфера
int64_t TV8FileStream::Read(void *Buffer, int64_t Count)
{
	int64_t r = file->read(Buffer, pos, Count);
	pos += r;
	return r;
}

//---------------------------------------------------------------------------
// чтение буфера
int TV8FileStream::Read(std::vector<uint8_t> Buffer, int Offset, int Count)
{
	int64_t r = file->read(Buffer, pos, Count);
	pos += r;
	return r;
}

//---------------------------------------------------------------------------
// запись буфера
int64_t TV8FileStream::Write(const void *Buffer, int64_t Count)
{
	int64_t r = file->write(Buffer, pos, Count);
	pos += r;
	return r;
}

//---------------------------------------------------------------------------
// запись буфера
int TV8FileStream::Write(const std::vector<uint8_t> Buffer, int Offset, int Count)
{
	int64_t r = file->write(Buffer, pos, Count);
	pos += r;
	return r;
}

//---------------------------------------------------------------------------
// позиционирование
int64_t TV8FileStream::Seek(const int64_t Offset, const TSeekOrigin Origin)
{
	int64_t len = file->get_file_length();
	switch(Origin)
	{
		case soFromBeginning:
			if(Offset >= 0)	{
				if(Offset <= len) {
					pos = Offset;
				}
				else {
					pos = len;
				}
			}
			break;
		case soFromCurrent:
			if(pos + Offset < len) {
				pos += Offset;
			}
			else {
				pos = len;
			}
			break;
		case soFromEnd:
			if(Offset <= 0) {
				if(Offset <= len) {
					pos = len - Offset;
				}
				else {
					pos = 0;
				}
			}
			break;
	}
	return pos;
}

int64_t TV8FileStream::GetSize() const
{
	return file->get_file_length();
}
