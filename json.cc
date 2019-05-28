#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace reed {

class json {
 public:
  json() : type_(kNull), key_(nullptr), idx_(-1) {}

  ~json() {}

  json(const json &rhs) {
    type_ = rhs.type_;
    if (rhs.type_ == kInteger) {
      i_ = rhs.i_;
    } else if (rhs.type_ == kDouble) {
      d_ = rhs.d_;
    } else if (rhs.type_ == kString) {
      s_ = rhs.s_;
    } else if (rhs.type_ == kList) {
      l_ = rhs.l_;
    } else if (rhs.type_ == kObject) {
      o_ = rhs.o_;
    }
  }

  operator int() {
    if (type_ == kInteger) {
      return i_;
    }
    return 0;
  }

  operator double() {
    if (type_ == kDouble) {
      return d_;
    }
    return 0.0;
  }

  operator std::string() {
    if (type_ == kString) {
      return s_;
    }
    return "";
  }

  json &operator[](const char *key) {
    key_ = key;
    o_iter it = o_.find(key_);
    if (it != o_.end()) {
      return it->second;
    }
    return *this;
  }

  json &operator[](int idx) {
    idx_ = idx;
    return *this;
  }

  json &operator=(int v) {
    if (key_ != nullptr) {
      type_ = kObject;
      json j;
      j = v;
      o_[key_] = j;
      key_ = nullptr;
    } else if (idx_ != -1) {
      type_ = kList;
      json j;
      j = v;
      if (l_.size() <= idx_) {
        l_.resize(idx_ + 1);
      }
      l_[idx_] = j;
      idx_ = -1;
    } else {
      type_ = kInteger;
      i_ = v;
    }
    return *this;
  }

  json &operator=(double v) {
    if (key_ != nullptr) {
      type_ = kObject;
      json j;
      j = v;
      o_[key_] = j;
      key_ = nullptr;
    } else if (idx_ != -1) {
      type_ = kList;
      json j;
      j = v;
      if (l_.size() <= idx_) {
        l_.resize(idx_ + 1);
      }
      l_[idx_] = j;
      idx_ = -1;
    } else {
      type_ = kDouble;
      d_ = v;
    }
    return *this;
  }

  json &operator=(const std::string &v) {
    if (key_ != nullptr) {
      type_ = kObject;
      json j;
      j = v;
      o_[key_] = j;
      key_ = nullptr;
    } else if (idx_ != -1) {
      type_ = kList;
      json j;
      j = v;
      if (l_.size() <= idx_) {
        l_.resize(idx_ + 1);
      }
      l_[idx_] = j;
      idx_ = -1;
    } else {
      type_ = kString;
      s_ = v;
    }
    return *this;
  }

  json &operator=(const json &v) {
    if (key_ != nullptr) {
      type_ = kObject;
      json j;
      j = v;
      o_[key_] = j;
      key_ = nullptr;
    } else if (idx_ != -1) {
      type_ = kList;
      json j;
      j = v;
      if (l_.size() <= idx_) {
        l_.resize(idx_ + 1);
      }
      l_[idx_] = j;
      idx_ = -1;
    } else {
      type_ = v.type_;
      if (v.type_ == kInteger) {
        i_ = v.i_;
      } else if (v.type_ == kDouble) {
        d_ = v.d_;
      } else if (v.type_ == kString) {
        s_ = v.s_;
      } else if (v.type_ == kList) {
        l_ = v.l_;
      } else if (v.type_ == kObject) {
        o_ = v.o_;
      }
    }
    return *this;
  }

  void debug() {
    switch (type_) {
      case kNull:
        printf("null");
        break;
      case kInteger:
        printf("%d", i_);
        break;
      case kDouble:
        printf("%lf", d_);
        break;
      case kString:
        printf("%s", s_.c_str());
        break;
      case kObject:
        printf("{");
        for (o_iter it = o_.begin(), it1 = it; it != o_.end(); ++it) {
          ++it1;
          printf("%s:", it->first.c_str());
          it->second.debug();
          if (it1 != o_.end()) {
            printf(",");
          }
        }
        printf("}\n");
        break;
      case kList:
        printf("[");
        for (l_iter it = l_.begin(), it1 = it; it != l_.end(); ++it) {
          ++it1;
          it->debug();
          if (it1 != l_.end()) {
            printf(",");
          }
        }
        printf("]\n");
        break;
      default:
        printf("unknown type: %d\n", type_);
    }
  }

 private:
  enum Type {
    kNull = 1,
    kTrue,
    kFalse,
    kInteger,
    kDouble,
    kString,
    kList,
    kObject
  };
  typedef std::vector<json>::iterator l_iter;
  typedef std::map<std::string, json>::iterator o_iter;
  Type type_;
  const char *key_;
  int idx_;
  int i_;
  double d_;
  std::string s_;
  std::vector<json> l_;
  std::map<std::string, json> o_;
};

}  // namespace reed

typedef reed::json json;

int main(int argc, char *argv[]) {
  json j, j1;

  /*
  j1[0] = 1;
  j1[10] = 2.2;
  j1[20] = "ccc";

  j["a"] = 1;
  j["b"] = 2.2;
  j["c"] = "ccc";

  j["k"] = j1;
  j1[11] = j;

  j.debug();
  j1.debug();
  */

  j1["in"] = "_internal_";
  j1["out"] = 99.8877;

  j["a"] = 3;
  j["xx"] = 123.0;
  j["b"] = 0.00001;
  j["s"] = "ssss";

  j["j"] = j1;

  j["t"] = false;

  j.debug();

  int a = j["a"];
  double b = j["b"];
  double xx = j["xx"];
  std::string s = j["s"];
  double out = j["j"]["out1"];
  printf("a=%d b=%lf xx=%lf s=%s out=%lf\n", a, b, xx, s.c_str(), out);

  j.debug();
}
