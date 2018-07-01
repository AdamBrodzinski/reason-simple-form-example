[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open ViewUtils;
open SimpleForm;

type schemaItem = {
  name: string,
  label: string,
};

let formSchema: list(schemaItem) = [
  {name: "firstName", label: "First name"},
];

let make = _children => {
  ...statelessComponent("MyForm"),
  render: _self =>
    <div className="MyForm">
      <Form>
        <TextInput name="firstName" unsafeProps={"autofocus": ""} />
      </Form>
    </div>,
};