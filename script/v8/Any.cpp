#include "Any.hpp"
#include "values.ipp"
#include "State.hpp"
#include "../../Exception.hpp"

BEGIN_INANITY_V8

Any::Any(ptr<State> state, v8::Local<v8::Value> value)
: state(state)
{
	this->value.Reset(state->GetIsolate(), value);
}

Any::~Any()
{
	value.Reset();
}

v8::Local<v8::Value> Any::GetV8Value() const
{
	return v8::Local<v8::Value>::New(state->GetIsolate(), value);
}

bool Any::IsNull() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsUndefined() || value->IsNull();
}

bool Any::IsBoolean() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsBoolean();
}

bool Any::IsNumber() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsNumber();
}

bool Any::IsString() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsString();
}

bool Any::IsArray() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsArray() || (value->IsObject() && !value->IsFunction() && value->ToObject()->InternalFieldCount() == 0);
}

bool Any::IsFunction() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsFunction();
}

bool Any::IsObject() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return value->IsObject()
		&& value->ToObject()->InternalFieldCount() == 1
		&& value->ToObject()->GetInternalField(0)->IsExternal();
}

ptr<RefCounted> Any::AsObject() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return Value<ptr<RefCounted> >::From(value);
}

bool Any::AsBool() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return Value<bool>::From(value);
}

int Any::AsInt() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return Value<int>::From(value);
}

float Any::AsFloat() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return Value<float>::From(value);
}

double Any::AsDouble() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return Value<double>::From(value);
}

String Any::AsString() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return Value<String>::From(value);
}

ptr<Script::Any> Any::CallWith(ptr<Script::Any> arguments[], int count)
{
	return ApplyWith(0, arguments, count);
}

ptr<Script::Any> Any::ApplyWith(ptr<Script::Any> thisValue, ptr<Script::Any> arguments[], int count)
{
	State::Scope scope(state);

	v8::TryCatch tryCatch;

#ifdef _DEBUG
	static const int maxArgs = 8;
	if(count > maxArgs)
		THROW("To many arguments for V8 function call");
#endif

	v8::Isolate* isolate = state->GetIsolate();

	v8::Local<v8::Value> args[8];
	for(int i = 0; i < count; ++i)
		args[i] = v8::Local<v8::Value>::New(isolate, fast_cast<Any*>(&*arguments[i])->value);

	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(isolate, this->value);
	v8::Local<v8::Value> v8ThisValue = thisValue
		? v8::Local<v8::Value>::New(isolate, fast_cast<Any*>(&*thisValue)->value)
		: v8::Local<v8::Value>(v8::Undefined(isolate));

	v8::Local<v8::Value> returnValue = v8::Function::Cast(*value)->Call(v8ThisValue, count, args);

	state->ProcessErrors(tryCatch);

	return state->CreateAny(returnValue);
}

int Any::GetLength() const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return (int)v8::Array::Cast(*value)->Length();
}

ptr<Script::Any> Any::Get(int index) const
{
	State::Scope scope(state);
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(state->GetIsolate(), this->value);
	return state->CreateAny(v8::Object::Cast(*value)->Get((uint32_t)index));
}

ptr<Script::Any> Any::Get(ptr<Script::Any> index) const
{
	State::Scope scope(state);
	v8::Isolate* isolate = state->GetIsolate();
	v8::Local<v8::Value> value = v8::Local<v8::Value>::New(isolate, this->value);
	return state->CreateAny(v8::Object::Cast(*value)->Get(
		v8::Local<v8::Value>::New(isolate, fast_cast<Any*>(&*index)->value)));
}

void Any::Set(int index, ptr<Script::Any> value)
{
	State::Scope scope(state);
	v8::Isolate* isolate = state->GetIsolate();
	v8::Local<v8::Value> array = v8::Local<v8::Value>::New(isolate, this->value);
	v8::Object::Cast(*array)->Set(
		(uint32_t)index,
		v8::Local<v8::Value>::New(isolate, fast_cast<Any*>(&*value)->value));
}

void Any::Set(ptr<Script::Any> index, ptr<Script::Any> value)
{
	State::Scope scope(state);
	v8::Isolate* isolate = state->GetIsolate();
	v8::Local<v8::Value> array = v8::Local<v8::Value>::New(isolate, this->value);
	v8::Object::Cast(*array)->Set(
		v8::Local<v8::Value>::New(isolate, fast_cast<Any*>(&*index)->value),
		v8::Local<v8::Value>::New(isolate, fast_cast<Any*>(&*value)->value));
}

void Any::Dump(std::ostream& stream) const
{
	THROW("Not implemented yet");
}

END_INANITY_V8
