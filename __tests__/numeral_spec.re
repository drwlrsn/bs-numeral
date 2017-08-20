open Jest;

open NumeralRe;

/* note that this is an interops test, not tests for numeral.js itself, i.e. test comprehensiveness is not the goal */
let () =
  describe
    "numeral"
    ExpectJs.(
      fun () => {
        test "#value" (fun () => expect (numeral Float 1000.1 |> Numeral.value) |> toBe 1000.1);
        test "#value" (fun () => expect (numeral Float 1000. |> Numeral.value) |> toBe 1000.);
        test
          "#value (> 32bit int)"
          (
            fun () => expect (numeral Float 3467479682787. |> Numeral.value) |> toBe 3467479682787.
          );
        /* Should return NaN, but instead returns 8637. &shrug; See #format time test */
        test
          "#value (time)"
          (fun () => expect (numeral String "2:23:57" |> Numeral.value) |> toBe 8637.);
        test
          "#format (thousands)"
          (fun () => expect (numeral Float 1000. |> Numeral.format "0,0") |> toBe "1,000");
        test
          "#format (cardinal)"
          (fun () => expect (numeral Float 100. |> Numeral.format "0o") |> toBe "100th");
        test
          "#format currency"
          (
            fun () =>
              expect (numeral Float (-1000.154) |> Numeral.format "$0,0.00") |> toBe "-$1,000.15"
          );
        test
          "#format bytes"
          (fun () => expect (numeral Float 1024. |> Numeral.format "0b") |> toBe "1KB");
        test
          "#format bytes (>32bit int)"
          (
            fun () =>
              expect (numeral Float 3467479682787. |> Numeral.format "0.000 ib") |>
              toBe "3.154 TiB"
          );
        test
          "#format percentages"
          (
            fun () =>
              expect (numeral Float 0.974878234 |> Numeral.format "0.000%") |> toBe "97.488%"
          );
        test
          "#format time"
          (fun () => expect (numeral Float 8637. |> Numeral.format "00:00:00") |> toBe "2:23:57");
        test
          "#format exponential"
          (
            fun () =>
              expect (numeral Float 12398734.202 |> Numeral.format "0.00e+0") |> toBe "1.24e+7"
          );
        test
          "#add"
          (
            fun () =>
              expect (numeral Float 100. |> Numeral.add num::100. |> Numeral.value) |> toBe 200.
          );
        test
          "#subtract"
          (
            fun () =>
              expect (numeral Float 100. |> Numeral.subtract num::10. |> Numeral.value) |> toBe 90.
          );
        test
          "#divide"
          (
            fun () =>
              expect (numeral Float 85. |> Numeral.divide num::10. |> Numeral.value) |> toBe 8.5
          );
        test
          "#multiply"
          (
            fun () =>
              expect (numeral Float 3.2 |> Numeral.multiply num::10. |> Numeral.value) |> toBe 32.
          );
        test
          "#difference"
          (fun () => expect (numeral String "28.9" |> Numeral.difference 12.3) |> toBe 16.6)
      }
    );