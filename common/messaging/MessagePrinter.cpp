/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * MessagePrinter.cpp
 * Prints the test representation of a Message.
 * Copyright (C) 2011 Simon Newton
 */


#include <ola/messaging/Message.h>
#include <ola/messaging/MessagePrinter.h>
#include <iostream>
#include <string>

namespace ola {
namespace messaging {


using std::string;
using std::endl;


void MessagePrinter::Visit(const BoolMessageField *message) {
  m_str << string(m_indent, ' ') << message->GetDescriptor()->Name() << ": " <<
    (message->Value() ? "true" : "false") << endl;
}


void MessagePrinter::Visit(const StringMessageField *message) {
  m_str << string(m_indent, ' ') << message->GetDescriptor()->Name() << ": " <<
    message->Value()<< endl;
}


void MessagePrinter::Visit(const BasicMessageField<uint8_t> *message) {
  const UInt8FieldDescriptor *descriptor = message->GetDescriptor();
  AppendUInt(descriptor->Name(),
             message->Value(),
             descriptor->LookupValue(message->Value()),
             descriptor->Multiplier());
}


void MessagePrinter::Visit(const BasicMessageField<uint16_t> *message) {
  const UInt16FieldDescriptor *descriptor = message->GetDescriptor();
  AppendUInt(descriptor->Name(),
             message->Value(),
             descriptor->LookupValue(message->Value()),
             descriptor->Multiplier());
}


void MessagePrinter::Visit(const BasicMessageField<uint32_t> *message) {
  const UInt32FieldDescriptor *descriptor = message->GetDescriptor();
  AppendUInt(descriptor->Name(),
             message->Value(),
             descriptor->LookupValue(message->Value()),
             descriptor->Multiplier());
}


void MessagePrinter::Visit(const BasicMessageField<int8_t> *message) {
  const Int8FieldDescriptor *descriptor = message->GetDescriptor();
  AppendInt(descriptor->Name(),
            message->Value(),
            descriptor->LookupValue(message->Value()),
            descriptor->Multiplier());
}


void MessagePrinter::Visit(const BasicMessageField<int16_t> *message) {
  const Int16FieldDescriptor *descriptor = message->GetDescriptor();
  AppendInt(descriptor->Name(),
            message->Value(),
            descriptor->LookupValue(message->Value()),
            descriptor->Multiplier());
}


void MessagePrinter::Visit(const BasicMessageField<int32_t> *message) {
  const Int32FieldDescriptor *descriptor = message->GetDescriptor();
  AppendInt(descriptor->Name(),
            message->Value(),
            descriptor->LookupValue(message->Value()),
            descriptor->Multiplier());
}


void MessagePrinter::Visit(const GroupMessageField *message) {
  m_str << string(m_indent, ' ') << message->GetDescriptor()->Name() << " {"
    << endl;
  m_indent += m_indent_size;
}


void MessagePrinter::PostVisit(const GroupMessageField *message) {
  m_indent -= m_indent_size;
  m_str << string(m_indent, ' ') << "}" << endl;
  (void) message;
}


void MessagePrinter::AppendUInt(const string &name,
                                unsigned int value,
                                const string &label,
                                int8_t multipler) {
  m_str << string(m_indent, ' ') << name << ": ";
  if (label.empty()) {
    m_str << value;
    AppendMultipler(multipler);
  } else {
    m_str << label;
  }
  m_str << endl;
}


void MessagePrinter::AppendInt(const string &name,
                               int value,
                               const string &label,
                               int8_t multipler) {
  m_str << string(m_indent, ' ') << name << ": ";
  if (label.empty()) {
    m_str << value;
    AppendMultipler(multipler);
  } else {
    m_str << label;
  }
  m_str << endl;
}


void MessagePrinter::AppendMultipler(int8_t multipler) {
  if (multipler)
    m_str << " x 10 ^ " << static_cast<int>(multipler);
}
}  // messaging
}  // ola