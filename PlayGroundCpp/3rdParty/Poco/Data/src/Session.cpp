//
// Session.cpp
//
// $Id: //poco/1.3/Data/src/Session.cpp#2 $
//
// Library: Data
// Package: DataCore
// Module:  Session
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/Data/Session.h"
#include "Poco/Data/SessionFactory.h"
#include <algorithm>


namespace Poco {
namespace Data {


Session::Session(Poco::AutoPtr<SessionImpl> ptrImpl):
	_ptrImpl(ptrImpl),
	_statementCreator(ptrImpl)
{
	poco_check_ptr (ptrImpl.get());
}


Session::Session(const std::string& connector, const std::string& connectionString)
{
	Session newSession(SessionFactory::instance().create(connector, connectionString));
	swap(newSession);
}


Session::Session(const Session& other):
	_ptrImpl(other._ptrImpl),
	_statementCreator(other._ptrImpl)
{
}


Session::~Session()
{
}


Session& Session::operator = (const Session& other)
{
	Session tmp(other);
	swap(tmp);
	return *this;
}


void Session::swap(Session& other)
{
	using std::swap;
	swap(_statementCreator, other._statementCreator);
	swap(_ptrImpl, other._ptrImpl);
}


} } // namespace Poco::Data