[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open ViewUtils;
open SF_Types;
open SimpleForm;

let formSchema: list(schemaItem) = [
  {name: "firstName", label: "First name"},
  {name: "lastName", label: "Last name"},
  {name: "age", label: "Age"},
];

let make = _children => {
  ...statelessComponent("MyForm"),
  render: _self =>
    <div className="MyForm">
      <Form schema=formSchema>
        <TextInput name="firstName" unsafeProps={"autofocus": ""} />
        <TextInput name="lastName" beforeUpdate=String.lowercase />
        <IntInput name="age" />
        <Submit text="Submit" />
      </Form>
    </div>,
};