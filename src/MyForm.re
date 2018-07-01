[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open ViewUtils;
open SimpleForm;

type schemas = list(Form.schemaItem);

let formSchema: schemas = [
  {name: "firstName", label: "First name"},
  {name: "lastName", label: "Last name"},
];

let make = _children => {
  ...statelessComponent("MyForm"),
  render: _self =>
    <div className="MyForm">
      <Form>
        <TextInput
          name="firstName"
          formSchema
          unsafeProps={"autofocus": ""}
        />
        <TextInput name="lastName" formSchema />
      </Form>
    </div>,
};