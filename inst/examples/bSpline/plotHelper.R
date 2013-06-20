
library(Rcpp)
sourceCpp("bSpline.cpp")                # compile two functions
dat <- genData()                        # generate the data
fit <- fitData(dat)                     # fit the model, returns matrix and gof measures

op <- par(mar=c(3,3,1,1))
plot(dat[,"x"], dat[,"y"], pch=19, col="#00000044")
lines(fit[[1]], fit[[2]], col="orange", lwd=2)
par(op)

#spl <- read.table("/tmp/spline.txt")
#splA <- spl[1:200,]
#splB <- spl[-c(1:200),]
#pdf("/tmp/plotHelper.pdf")
#op <- par(mar=c(3,3,1,1))
#plot(splA, pch=19, col="#00000044")
#lines(splB, col="orange")
#par(op)
#dev.off()

