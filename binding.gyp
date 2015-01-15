{
  "targets": [
    {
      "target_name": "lttng",
      "sources": [ "./src/lttng.cc", "./src/lttng-tp.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")", "./src" ],
      "libraries": [ "-llttng-ust" ]
    }
  ]
}