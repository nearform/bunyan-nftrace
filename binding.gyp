{
  "targets": [
    {
      "target_name": "lttng",
      "sources": [ "./src/lttng.cc", "./src/lttng-tp.c" ],
      "include_dirs": [ "./src" ],
      "libraries": [ "-llttng-ust" ]
    }
  ]
}