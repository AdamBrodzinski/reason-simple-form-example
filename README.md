# Work in Progress

Demo Link: [reason-simple-form-example.netlify.com](https://reason-simple-form-example.netlify.com)

## Example App for [reason-simple-form](https://github.com/AdamBrodzinski/reason-simple-form)

This repo is a sandbox to build out the simple form module and then will turn into an app that requires the completed package. I'm aiming at having a 1.0 version finished by the end of August. I'll also be using this production so it's not going to turn into vaporware.

https://github.com/AdamBrodzinski/reason-simple-form

Example:

```javascript
/* optional default/starter CSS for prototyping */
[%bs.raw {| require('reason-simple-form/default.css') |}];
open SimpleForm;

let component = ReasonReact.reducerComponent("SignupForm");

let formSchema: SimpleForm.schemaList = [
  {name: "username", castType: `String, label: "Username", validations: [MinLen(2), MaxLen(20)]},
  {name: "email",  castType: `String, label: "email", validations: [Email]},
  {name: "age", castType: `Int, label: "Age", validations: [Regex(myRegex, "Invalid Age")]},
];

let handleSubmit = (~sendLoaded, form: formState) => {
  Js.log(form);
  Js.Global.setTimeout(() => sendLoaded(), 1500);
};

let make = _children => {
  ...component,
  render: _self =>
    <Form schema=formSchema onSubmit=handleSubmit>
      <Input name="username" />
      <Input name="email" beforeUpdate=String.lowercase />
      <Input name="age" />
      <Submit text="Sign Up" loadingText="Saving..." />
    </Form>,
};
```

Optional CSS Included

![Screenshot](https://i.imgur.com/HfuMPdo.png)

TODO list:

- [x] default css
- [x] text input
- [x] text area input
- [x] radio input
- [x] integer input
- [x] float input
- [x] checkbox input
- [x] select input
- [x] submit loading indicator/sendLoaded action
- [x] move input types to schema
- [x] consolidate textbox inputs into one `<Input />` component
- [x] finish missing validations (like `RequiredWithMsg(string)`)
- [ ] allow for default values or prefilling fields with data
- [ ] cast values into their type before sending to `onSubmit` handler
- [ ] better exceptions for invalid configurations
- [ ] move over to separate repo and release to NPM
- [ ] add tests for React
- [ ] create interface files & add function docs
- [ ] add support for JS react apps?

**TEMP documentation** this is incomplete

Simple Form tries to be flexible enough to cover 80% of the use cases. If you need more configurability you can always connect to the React context and buildup a custom input/validation as needed.

### Form

The form component is a wrapper around the inputs that sets up form state and a context. The onSubmit handler allows you to catch the changes on submit. All of the form values are in their original string type to maintain simplicity. I may change this before releasing a 1.0.

```javascript
// onSubmit data example:
{
  inputStates: [
    {name: "username", value: "Jane23", valid: true, dirty: true, errors: [] }
    {name: "age", value: "47", valid: true, dirty: true, errors: [] }
    {name: "extraInfo", value: "", valid: false, dirty: false, errors: [
      {kind: "required", "This field is required"}
    ] }
  ],
  isValid: true,
  submitted: true
}
```

### Schema

The schema list allows you to describe how the input should be validated and what it's label should be. If you need to translate the labels or error messages you can map those into a function that you provide.

```javascript
{ name: string, label: string, validations: list(validations) }
```

### Validations

note, all of these should have a `WithMsg` variant soon to provide custom error messages. Other constructors will be coming soon but these should cover a lot of cases.

- `Required` Requires that any non empty string is entered into the input
- `Email` Requires that a simple email regex matches (`a@b.`) is valid
- `EmailWithMsg(string)` Email but it has a custom error message
- `Regex(Js.Re.t, string)` Custom regex matcher with custom error message
- `MinLen(int)` String length must be greater or equal to integer value
- `MaxLen(int)` String length must less than or equal to integer value
- `Func((inputState, formState) => (bool, string))` Custom validator function to read input data and return answer

### Inputs

Componet names assume you are using `open SimpleForm`, otherwise add namespace: `SimpleForm_TextInput`

- `Submit` - Optional submit button (you can use your own if you wish). This one has support for text that changes and disables when the form is in a loading state. Props: `text: string loadingText?: string`

```javascript
<Submit text="Sign Up" loadingText="Updating..." />
```

- `TextInput` - Normal text input.

```javascript
<TextInput name="firstName" />
```

- `IntInput` - Only accept valid `int_of_string` characters. Any invalid values will be dropped and never updated.

```javascript
<IntInput name="age" />
```

- `FloatInput` - Only accepts valid `float_of_string` characters. Any invalid values will be dropped and never updated.

```javascript
<FloatInput name="income" />
```

- `Radio` -

```javascript
  <Radio
    name="color"
    radioValues=[ ("Red", "red"), ("Green", "green")]
  />
```

- `Checkbox` - Standard checkbox. returns value `"true"` or `"false"`

```javascript
<IntInput name="age" />
```

### Input Props

Currently inputs have a `name`, `beforeUpdate`, and `unsafeProps` props. These will be more complete soon but are minimal to enable easier change before the API is settled on.

- `name` `string` _Required_ Pass in input attribute name. This name will also be used in the schema
- `beforeUpdate` `(string) => string` Allows you to transform the input value before it's saved into form state. This is handy to force casing or other special use cases.
- `unsafeProps` `{.}` - Pass any props unsafely into the react component. These props go into each input only (perhaps in the future i'll add a unsafeLabelProps and unsafeErrorProps props)
