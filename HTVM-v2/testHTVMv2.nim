

# Print function for various types
proc print(value: auto) =  # Use 'auto' instead of 'untyped'
  # Nim uses when/elif for type checking, not case
  when value is string:
    echo value
  elif value is int or value is float:
    echo $value  # Use $ for string conversion in Nim
  elif value is bool:
    echo if value: "true" else: "false"
  else:
    echo "Unsupported type"

proc HTVM_Append[T](arr: var seq[T], value: T) =
  arr.add(value)

proc HTVM_Size[T](arr: seq[T]): int =
  return arr.len


for A_Index1 in 0..5 + 0:
    print("hello HTVM v2")
    print("hello HTVM\nv2")
    print(A_Index1)
    for A_Index2 in 0..5 + 0:
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        for A_Index3 in 0..5 + 0:
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index3)
        print(A_Index2)
print(5+5 != 5 not SZDS() and "A+-+--+ != ADSF" and "WSADFD" and "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
print(if "QWADSDF" and "qawdsf" || var1 ! var4 and "ASDFX" and not ADSFD("Qwads" and "QASD" and "aszd" < 6): false else: true || nil && false)
print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
var1 = 1
print(if (var1 == 1): "hello" else: "bye")
var1 = 0
print(if (var1 == 1): "hello" else: "bye")
