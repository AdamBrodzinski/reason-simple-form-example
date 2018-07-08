[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open ViewUtils;
open SF_Types;
open SimpleForm;

type state = {loading: bool};

type action =
  | Loading
  | Loaded;

let component = ReasonReact.reducerComponent("MyForm");

let formSchema: list(schemaItem) = [
  {name: "firstName", label: "First name"},
  {name: "lastName", label: "Last name"},
  {name: "age", label: "Age"},
];

let make = _children => {
  let handleSubmit = (formState, self) => {
    Js.log("Submit form");
    Js.log(formState);
    self.ReasonReact.send(Loaded);
  };

  {
    ...component,
    initialState: () => {loading: false},
    reducer: (action, _state) =>
      switch (action) {
      | Loading => ReasonReact.Update({loading: true})
      | Loaded => ReasonReact.Update({loading: false})
      },
    render: self =>
      <div className="MyForm">
        <Form schema=formSchema onSubmit=(self.handle(handleSubmit))>
          <TextInput name="firstName" unsafeProps={"autofocus": ""} />
          <TextInput name="lastName" beforeUpdate=String.lowercase />
          <IntInput name="age" />
          <Submit text="Update" isLoading=self.state.loading />
        </Form>
      </div>,
  };
};