let component = ReasonReact.statelessComponent("Snake");

let make = (~coordinates, ~dead, _children) => {
  ...component,
  render: _self =>
    <g>
      (
        ReasonReact.array(
          Array.of_list(
            List.mapi(
              (index, coordinate) =>
                <SnakePart key=(string_of_int(index)) coordinate dead />,
              coordinates,
            ),
          ),
        )
      )
    </g>,
};