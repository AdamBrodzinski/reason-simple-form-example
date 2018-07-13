[%bs.raw {|require('./SimpleForm/simple-form.css')|}];
open SF_Types;
open SimpleForm;

type state = {loading: bool};

type action =
  | Loading
  | Loaded;

let component = ReasonReact.reducerComponent("MyForm");

let formSchema = [
  {
    name: "firstName",
    label: "First name",
    validations: [Regex([%re "/foo/i"], "Foo required!")],
  },
  {
    name: "lastName",
    label: "Last name",
    validations: [] /*Required, Min(3), Max(10)*/,
  },
  {name: "age", label: "Age", validations: []},
];

let make = _children => {
  let handleSubmit = (formState, self) => {
    Js.log("Submit form");
    Js.log(formState.inputStates |> Array.of_list);
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
          <TextInput name="firstName" />
          /*
           <TextInput name="lastName" beforeUpdate=String.lowercase />
           <IntInput name="age" />
           */
          <Submit text="Update" isLoading=self.state.loading />
        </Form>
      </div>,
  };
};