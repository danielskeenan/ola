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
 * StringMessageBuilder.cpp
 * Builds a Message object from a list of strings & a Descriptor.
 * Copyright (C) 2011 Simon Newton
 */


#include <ola/Logging.h>
#include <ola/StringUtils.h>
#include <ola/messaging/Descriptor.h>
#include <ola/messaging/Message.h>
#include <ola/rdm/StringMessageBuilder.h>
#include <string>
#include <vector>

namespace ola {
namespace rdm {

using ola::messaging::MessageFieldInterface;


const ola::messaging::Message *StringMessageBuilder::GetMessage() const {
  if (m_error)
    return NULL;
  return new ola::messaging::Message(m_messages);
}


/**
 * Bool values can be true,false,0,1
 */
void StringMessageBuilder::Visit(
    const ola::messaging::BoolFieldDescriptor *descriptor) {
  if (StopParsing())
    return;

  bool value = false;
  bool valid = false;
  string token = m_inputs[m_offset++];
  ola::StringTrim(&token);
  ola::ToLower(&token);

  if (token == "true") {
    valid = value = true;
  } else if (token == "false") {
    value = false;
    valid = true;
  }

  if (!valid) {
    uint8_t int_value;
    if (ola::StringToUInt8(token, &int_value)) {
      if (int_value == 1) {
        valid = value = true;
      } else if (int_value == 0) {
        valid = true;
        value = false;
      }
    }
  }

  if (!valid) {
    SetError(descriptor->Name());
    return;
  }

  m_messages.push_back(
      new ola::messaging::BoolMessageField(descriptor, value));
}


/**
 * Handle strings
 */
void StringMessageBuilder::Visit(
    const ola::messaging::StringFieldDescriptor *descriptor) {
  if (StopParsing())
    return;

  const string &token = m_inputs[m_offset++];
  if (descriptor->MaxSize() != 0 &&
      token.size() > descriptor->MaxSize()) {
    SetError(descriptor->Name());
    return;
  }

  m_messages.push_back(
      new ola::messaging::StringMessageField(descriptor, token));
}


/**
 * uint8
 */
void StringMessageBuilder::Visit(
    const ola::messaging::UInt8FieldDescriptor *descriptor) {
  VisitInt(descriptor);
}


void StringMessageBuilder::Visit(
    const ola::messaging::UInt16FieldDescriptor *descriptor) {
  VisitInt(descriptor);
}


void StringMessageBuilder::Visit(
    const ola::messaging::UInt32FieldDescriptor *descriptor) {
  VisitInt(descriptor);
}


void StringMessageBuilder::Visit(
    const ola::messaging::Int8FieldDescriptor *descriptor) {
  VisitInt(descriptor);
}


void StringMessageBuilder::Visit(
    const ola::messaging::Int16FieldDescriptor *descriptor) {
  VisitInt(descriptor);
}


void StringMessageBuilder::Visit(
    const ola::messaging::Int32FieldDescriptor *descriptor) {
  VisitInt(descriptor);
}


void StringMessageBuilder::Visit(
    const ola::messaging::GroupFieldDescriptor *descriptor) {
  vector<const MessageFieldInterface*> fields;
  m_groups.push(fields);
  (void) descriptor;
}


void StringMessageBuilder::PostVisit(
    const ola::messaging::GroupFieldDescriptor *descriptor) {
  if (m_groups.empty()) {
    OLA_FATAL << "Mismatched group exit call, this is a programming bug!";
    return;
  }

  const vector<const MessageFieldInterface*> &fields = m_groups.top();
  m_messages.push_back(
      new ola::messaging::GroupMessageField(descriptor, fields));
  m_groups.pop();
}


bool StringMessageBuilder::StopParsing() const {
  return m_error ||  m_offset >= m_input_size;
}


void StringMessageBuilder::SetError(const string &error) {
  m_error = true;
  m_error_string = error;
}


template<typename type>
void StringMessageBuilder::VisitInt(
    const ola::messaging::IntegerFieldDescriptor<type> *descriptor) {
  if (StopParsing())
    return;

  type int_value;
  if (ola::StringToInt(m_inputs[m_offset++], &int_value)) {
    m_messages.push_back(
        new ola::messaging::BasicMessageField<type>(descriptor, int_value));
  } else {
    SetError(descriptor->Name());
  }
}
}  // rdm
}  // ola
