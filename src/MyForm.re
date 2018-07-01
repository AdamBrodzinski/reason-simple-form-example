[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open ViewUtils;
open SimpleForm;

let make = _children => {
  ...statelessComponent("MyForm"),
  render: _self =>
    <div className="MyForm">
      <Form>
        <TextInput
          name="firstName"
          dangerousDomProps={"autofocus": "autofocus"}
        />
      </Form>
    </div>,
};