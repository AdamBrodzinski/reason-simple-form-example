open Jest;
open Expect;
open SimpleForm_Utils;

describe("SimpleForm_Utils", () => {
  test("inspect", () =>
    expect(3 + 3 |> inspect) |> toBe(6)
  );

  test("mapReactList", () => {
    let names = ["foo", "bar"];
    let result = mapReactList(names, (_i, name) => ReasonReact.string(name));
    let reference =
      List.mapi((_i, name) => ReasonReact.string(name), names)
      |> Array.of_list
      |> ReasonReact.array;
    expect(result) |> toEqual(reference);
  });

  test("fallbackFunc", () => {
    let defaultFunc = x => x;
    let myFunc = fallbackFunc(Some(x => x + 100), defaultFunc);
    let noFunc = fallbackFunc(None, defaultFunc);
    expect((myFunc(10), noFunc(10))) |> toEqual((110, 10));
  });

  test("isStringInteger", () => {
    let result1 = isStringInteger("$23");
    let result2 = isStringInteger("23");
    expect((result1, result2)) |> toEqual((false, true));
  });

  test("isStringFloat", () => {
    let result1 = isStringFloat("23.0 f");
    let result2 = isStringFloat("23.4");
    expect((result1, result2)) |> toEqual((false, true));
  });

  test("isStringBool", () => {
    expect(isStringBool("")) |> toBe(false) |> ignore;
    expect(isStringBool("null")) |> toBe(false) |> ignore;
    expect(isStringBool("false")) |> toBe(true) |> ignore;
    expect(isStringBool("true")) |> toBe(true);
  });

  test("intOfStringOrZero", () => {
    let _ = expect(intOfStringOrZero("1")) |> toBe(0);
    expect(intOfStringOrZero("1")) |> toBe(1);
  });
});