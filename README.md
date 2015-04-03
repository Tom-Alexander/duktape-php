#duktape-php
Experimental PHP extension for the [Duktape](http://duktape.org/) javascript interpreter.

## Usage
```
$input = file_get_contents('app.js');
$duktape = new Duktape();
$result = $duktape->eval($input);
```