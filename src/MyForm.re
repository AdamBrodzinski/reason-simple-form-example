[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open ViewUtils;
open SF_Types;
open SimpleForm;

let formSchema: list(schemaItem) = [
  {name: "firstName", label: "First name"},
  {name: "lastName", label: "Last name"},
  {name: "age", label: "Age"},
];

type state = {loading: bool};

type action =
  | Loading
  | Loaded;

let handleSubmit = (formState, self) => {
  Js.log("Submit form");
  Js.log("Submit form");
  self.ReasonReact.send(Loaded);
};

let make = _children => {
  ...reducerComponent("MyForm"),
  initialState: () => {loading: false},
  reducer: (action, _state) =>
    switch (action) {
    | Loading => ReasonReact.Update({loading: true})
    | Loaded => ReasonReact.Update({loading: false})
    },
  render: self =>
    <div className="MyForm">
      <Form schema=formSchema>
        <TextInput name="firstName" unsafeProps={"autofocus": ""} />
        <TextInput name="lastName" beforeUpdate=String.lowercase />
        <IntInput name="age" />
        <Submit text="Update" isLoading=self.state.loading />
      </Form>
    </div>,
};