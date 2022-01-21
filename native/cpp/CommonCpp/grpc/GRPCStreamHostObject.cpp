#include "GRPCStreamHostObject.h"
#import <jsi/jsi.h>

using namespace facebook;

GRPCStreamHostObject::GRPCStreamHostObject() : readyState{0} {
}

std::vector<jsi::PropNameID>
GRPCStreamHostObject::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> names;
  names.reserve(6);
  names.push_back(jsi::PropNameID::forUtf8(rt, std::string{"readyState"}));
  names.push_back(jsi::PropNameID::forUtf8(rt, std::string{"onopen"}));
  names.push_back(jsi::PropNameID::forUtf8(rt, std::string{"onmessage"}));
  names.push_back(jsi::PropNameID::forUtf8(rt, std::string{"onclose"}));
  names.push_back(jsi::PropNameID::forUtf8(rt, std::string{"close"}));
  names.push_back(jsi::PropNameID::forUtf8(rt, std::string{"send"}));
  return names;
}

jsi::Value GRPCStreamHostObject::get(
    jsi::Runtime &runtime,
    const jsi::PropNameID &propName) {
  auto name = propName.utf8(runtime);

  if (name == "readyState") {
    return jsi::Value(readyState);
  }

  return jsi::String::createFromUtf8(runtime, std::string{"unimplemented"});
}
