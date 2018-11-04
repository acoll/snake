let component = ReasonReact.statelessComponent("Goodies");

let make = (~goodies, _children) => {
  ...component,
  render: _self =>
    <g>
      (
        ReasonReact.array(
          Array.of_list(
            List.mapi(
              (index, (x, y)) =>
                <rect
                  key=(string_of_int(index))
                  x=(string_of_int(x) ++ "%")
                  y=(string_of_int(y) ++ "%")
                  width="1%"
                  height="1%"
                  fill="green"
                />,
              goodies,
            ),
          ),
        )
      )
    </g>,
};