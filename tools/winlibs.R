# Download GSL 2.4 Rtools build
if(!file.exists("../windows/gsl-2.4/include/gsl/gsl_blas.h")){
  download.file("https://github.com/rwinlib/gsl/archive/v2.4.zip", "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}
