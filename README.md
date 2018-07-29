# Work in Progress

## Example App for reason-simple-form

This repo is a sandbox to build out the simple form module and then will turn into an app that requires the completed package.

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
