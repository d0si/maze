#include <Maze/Maze.hpp>
#include <Maze/Object.hpp>
#include <Maze/Helpers.hpp>
#include <nlohmann/json.hpp>

namespace Maze {
	Element::Element() {

	}

	Element::Element(const Element& val) {
		set_element(val);
	}

	Element::Element(bool val) {
		set_bool(val);
	}

	Element::Element(int val) {
		set_int(val);
	}

	Element::Element(double val) {
		set_double(val);
	}

	Element::Element(const std::string& val) {
		set_string(val);
	}

	Element::Element(const char* val) {
		set_string(val);
	}

	Element::Element(const Array& val) {
		set_array(val);
	}

	Element::Element(const Object& val) {
		set_object(val);
	}

	Element::Element(Type type) {
		set_type(type);
	}

	Element::~Element() {

	}
	
	void Element::set_element(const Element& val) {
		switch (val.get_type()) {
		case Type::Null:
			set_null();
			break;
		case Type::Bool:
			set_bool(val.get_bool());
			break;
		case Type::Int:
			set_int(val.get_int());
			break;
		case Type::Double:
			set_double(val.get_double());
			break;
		case Type::String:
			set_string(val.get_string());
			break;
		case Type::Array:
			set_array(val.get_array());
			break;
		case Type::Object:
			set_object(val.get_object());
			break;
		default:
			set_null();
		}
	}

	void Element::operator=(const Element& val) {
		set_element(val);
	}

	void Element::set_type(Type type) {
		switch (type) {
		case Type::Null:
			set_null();
			break;
		case Type::Bool:
			set_bool(false);
			break;
		case Type::Int:
			set_int(0);
			break;
		case Type::Double:
			set_double(0);
			break;
		case Type::String:
			set_string("");
			break;
		case Type::Array:
			set_array(Array());
			break;
		case Type::Object:
			set_object(Object());
			break;
		default:
			set_null();
		}
	}

	Type Element::get_type() const {
		return type_;
	}

	void Element::set_key(std::string key) {
		val_key_ = key;
	}

	std::string Element::get_key() const {
		return val_key_;
	}

	void Element::set_null() {
		if (type_ != Type::Null) {
			val_bool_ = false;
			val_int_ = 0;
			type_ = Type::Null;
		}
	}

	void Element::set_bool(bool val) {
		val_bool_ = val;
		type_ = Type::Bool;
	}

	void Element::operator=(bool val) {
		set_bool(val);
	}

	bool Element::get_bool() const {
		if (type_ == Type::Bool) {
			return val_bool_;
		}
		return false;
	}

	bool Element::b() const {
		return get_bool();
	}

	Element::operator bool() const {
		return get_bool();
	}

	void Element::set_int(int val) {
		val_int_ = val;
		type_ = Type::Int;
	}

	void Element::operator=(int val) {
		set_int(val);
	}

	int Element::get_int() const {
		if (type_ == Type::Int) {
			return val_int_;
		}

		return 0;
	}

	int Element::i() const {
		return get_int();
	}

	Element::operator int() const {
		return get_int();
	}

	void Element::set_double(double val) {
		val_double_ = val;
		type_ = Type::Double;
	}

	void Element::operator=(double val) {
		set_double(val);
	}

	double Element::get_double() const {
		if (type_ == Type::Double) {
			return val_double_;
		}

		return 0;
	}

	double Element::d() const {
		return get_double();
	}

	Element::operator double() const {
		return get_double();
	}

	void Element::set_string(const std::string& val) {
		val_string_ = val;
		type_ = Type::String;
	}

	void Element::operator=(const std::string& val) {
		set_string(val);
	}

	void Element::operator=(const char* val) {
		set_string(val);
	}

	std::string Element::get_string() const {
		if (type_ == Type::String) {
			return val_string_;
		}

		return "";
	}

	std::string Element::s() const {
		return get_string();
	}

	Element::operator std::string() const {
		return get_string();
	}

	void Element::set_array(const Array& val) {
		ptr_array_ = std::make_unique<Array>(val);
		type_ = Type::Array;
	}

	void Element::operator=(const Array& val) {
		set_array(val);
	}

	Array Element::get_array() const {
		if (type_ == Type::Array) {
			return *ptr_array_;
		}
		return Array();
	}

	Array Element::a() const {
		return get_array();
	}

	Array* Element::a_ptr() const {
		return ptr_array_.get();
	}

	Element::operator Array() const {
		return get_array();
	}

	void Element::set_object(const Object& val) {
		ptr_object_ = std::make_unique<Object>(val);
		type_ = Type::Object;
	}

	void Element::operator=(const Object& val) {
		set_object(val);
	}

	Object Element::get_object() const {
		if (type_ == Type::Object) {
			return *ptr_object_;
		}
		return Object();
	}

	Object Element::o() const {
		return get_object();
	}

	Object* Element::o_ptr() const {
		return ptr_object_.get();
	}

	Element::operator Object() const {
		return get_object();
	}

	bool Element::is_null() const {
		return is(Type::Null);
	}

	bool Element::is_bool() const {
		return is(Type::Bool);
	}

	bool Element::is_int() const {
		return is(Type::Int);
	}

	bool Element::is_double() const {
		return is(Type::Double);
	}

	bool Element::is_string() const {
		return is(Type::String);
	}

	bool Element::is_array() const {
		return is(Type::Array);
	}

	bool Element::is_object() const {
		return is(Type::Object);
	}

	bool Element::is(Type type) const {
		return (type_ == type);
	}

	void Element::apply(const Element& new_element) {
		switch (new_element.get_type()) {
		case Type::Null:
			set_null();
			break;
		case Type::Bool:
			set_bool(new_element.get_bool());
			break;
		case Type::Int:
			set_int(new_element.get_int());
			break;
		case Type::Double:
			set_double(new_element.get_double());
			break;
		case Type::String:
			set_string(new_element.get_string());
			break;
		case Type::Array:
			set_array(new_element.get_array());
			break;
		case Type::Object:
			ptr_object_->apply(new_element.get_object());
			break;
		}
	}

	std::string Element::to_json(int spacing) const {
		return Helpers::Element::to_json_element(this).dump(spacing);
	}

	void Element::apply_json(const std::string& json_string) {
		Helpers::Element::apply_json(this, nlohmann::json::parse(json_string));
	}

	Element Element::from_json(const std::string& json_string) {
		return Helpers::Element::from_json(nlohmann::json::parse(json_string));
	}

	Element Element::get_null() {
		Element el;
		el.set_null();
		return el;
	}
}  // namespace Maze
