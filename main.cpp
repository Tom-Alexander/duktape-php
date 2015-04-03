#include <phpcpp.h>
#include <iostream>

extern "C" {
  #include "duktape.h"
}

class Duktape : public Php::Base
{

private:
	duk_context *ctx = NULL;

public:
	Duktape() {
		ctx = duk_create_heap_default();
	}

	virtual ~Duktape() {
		duk_destroy_heap(ctx);
	}

	Php::Value eval(Php::Parameters &parameters) {
		const char *result;

		if (parameters.size() != 1) {
			throw Php::Exception("Error");
			return "";
		}

		duk_push_string(ctx, parameters[0]);
		int code = duk_peval(ctx);

		if (code != DUK_ERR_NONE) {
			switch (code)
			{
				case DUK_ERR_ERROR:
					throw Php::Exception("Error");
				break;
				case DUK_ERR_EVAL_ERROR:
					throw Php::Exception("EvalError");
				break;
				case DUK_ERR_RANGE_ERROR:
					throw Php::Exception("EvalError");
				break;
				case DUK_ERR_REFERENCE_ERROR:
					throw Php::Exception("ReferenceError");
				break;
				case DUK_ERR_SYNTAX_ERROR:
					throw Php::Exception("SyntaxError");
				break;
				case DUK_ERR_TYPE_ERROR:
					throw Php::Exception("TypeError");
				break;
				case DUK_ERR_URI_ERROR:
					throw Php::Exception("URIError");
				break;
				default:
					throw Php::Exception("Error");
				break;
			}
		}

		result = duk_safe_to_string(ctx, -1);
		return result;
	}
};

extern "C" {
    PHPCPP_EXPORT void *get_module() {
        static Php::Extension extension("duktape_php", "0.0.1");
        Php::Class<Duktape> duktape("Duktape");
		duktape.method("eval", &Duktape::eval);
		extension.add(std::move(duktape));
        return extension;
    }
}