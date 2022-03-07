add_executable(repeat
  repeat.c
)

set_property(TARGET repeat
  PROPERTY RUNTIME_OUTPUT_NAME sampler-repeat
)

install(TARGETS repeat RENAME sampler-repeat)
install(PROGRAMS fmtdot TYPE BIN RENAME sampler-fmtdot)
install(PROGRAMS fmtshort TYPE BIN RENAME sampler-fmtshort)
install(PROGRAMS fmttable TYPE BIN RENAME sampler-fmttable)
install(PROGRAMS process.py TYPE BIN RENAME sampler-process)
