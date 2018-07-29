# Work in Progress

## Example App for [reason-simple-form](https://github.com/AdamBrodzinski/reason-simple-form)

This repo is a sandbox to build out the simple form module and then will turn into an app that requires the completed package.

https://github.com/AdamBrodzinski/reason-simple-form

Example:

```javascript
/* optional default/starter CSS for prototyping */
[%bs.raw {| require('reason-simple-form/default.css') |}];
open SimpleForm;

let component = ReasonReact.reducerComponent("SignupForm");

let formSchema: SimpleForm.schemaList = [
  {name: "username", label: "Username", validations: [MinLen(2), MaxLen(20)]},
  {name: "email", label: "email", validations: [Email]},
  {name: "age", label: "Age", validations: [Regex(myRegex, "Invalid Age")]},
];

/* optional `sendLoaded` action stops loading indicator for optional Submit button */
let handleSubmit = (~sendLoaded, formState) =>
  myLoginUserFunc(formState.inputValues)
  |> then_(res => sendLoaded() });

let make = _children => {
  ...component,
  render: _self =>
    <Form schema=formSchema onSubmit=handleSubmit>
      <TextInput name="firstName" />
      <TextInput name="lastName" beforeUpdate=String.lowercase />
      <IntInput name="age" />
      <Submit text="Sign Up" savingText="Updating..." />
    </Form>,
};
```

### Quick Temp Documentation...

Simple Form tries to be flexible enough to cover 80% of the use cases. If you need more configurability you can always connect to the React context and buildup a custom input/validation as needed.

### Validations

note, all of these should have a `WithMsg` variant soon to provide custom error messages

  - `Required` Requires that any non empty string is entered into the input
  - `Email` Requires that a simple email regex matches (`a@b.`) is valid
  - `EmailWithMsg(string)` Email but it has a custom error message
  - `Regex(Js.Re.t, string)` Custom regex matcher with custom error message
  - `MinLen(int)` String length must be greater or equal to integer value
  - `MaxLen(int)` String length must less than or equal to integer value
  - `Func((inputState, formState) => (bool, string))` Custom validator function to read input data and return answer
  
### Input Props

Currently inputs have a `name`, `beforeUpdate`, and `unsafeProps` props. These will be more complete soon but are minimal to enable easier change before the API is settled on.

- `beforeUpdate` `(string) => string` Allows you to transform the input value before it's saved into form state. This is handy to force casing or other special use cases.
