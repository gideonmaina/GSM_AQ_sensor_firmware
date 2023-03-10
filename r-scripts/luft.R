source("installrequire.R")
installrequire(c("lubridate","dplyr","ggplot2"))
# library(xlsx)
# library(lubridate)
# library(dplyr)
# library(ggplot2)


###########################################################################
#####Preparation(only once)################################################
###########################################################################
#roh <- read.xlsx(file="table23032015135021029.xlsx", sheetIndex=1)
#names(roh) <- c("Messstelle", "Datetime", "Agg_Zeitraum", "Agg_Art", "NO2")
#roh$NO2 <- as.numeric(as.character(roh$NO2))
#roh$Datetime <- ymd_hm(roh$Datetime)
#roh <- roh %>% mutate(Woche=week(Datetime)) %>% mutate(Monat=month(Datetime)) %>% mutate(Date=as.Date(Datetime))

# script to read+preprocess (Makefile friendly)
# loads dataframe dat
source("readdata.R")
stop("readddata.R dysfct/not existent/moved to readairdat, stopping here...")


## Plots, to pdf
# pdf("plots.pdf")
png(width=1200,height=1000)

#Werte fuer PM2.5 im Zeitverlauf
p1 <- ggplot(filter(dat, type=="PPD42NS"), aes(timestamp2, P2, color=type)) + geom_point() + theme(axis.text.x = element_text(angle=90)) + geom_point(data=filter(dat, type == "GP2Y1010AU0F"), aes(timestamp2, P25, color=type)) + scale_y_log10()
#+ geom_point(data=filter(dat, type=="GP2Y1010AU0F"), aes(timestamp2, vo_raw, color=type))
print(p1)

# density plots
p1<-ggplot(dat, aes(x = P2)) + stat_density() + scale_x_log10()+ labs(title="P2 density (log scaled)")
print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + scale_x_log10() + labs(title="P1 density (log scaled)")
print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + scale_x_log10() + labs(title="P1 density (log scaled) by location_id")+ facet_wrap(~location_id); print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + xlim(c(-1000,15645))+ labs(title="P1 density")
print(p1)

p1<-ggplot(dat, aes(x = P1)) + stat_density() + xlim(c(-1000,15645))+ labs(title="P1 density per location_id")+ facet_wrap(~location_id); print(p1)

p1<-ggplot(dat, aes(x = ratioP1)) + stat_density() + labs(title="ratioP1 density") + xlim(c(0,15))
print(p1)
p1<-ggplot(dat, aes(x = ratioP1)) + stat_density() + labs(title="ratioP1 density by location_id") + xlim(c(0,15)) + facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = ratioP2)) + stat_density() + labs(title="ratioP2 density") + xlim(c(0,2))
print(p1)
p1<-ggplot(dat, aes(x = ratioP2)) + stat_density() + labs(title="ratioP2 density by location_id") + xlim(c(0,2)) + facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = ratioP2)) + stat_density() + labs(title="ratioP2 density") + xlim(c(0,15))
#+ scale_x_log10()
print(p1)

p1<-ggplot(dat, aes(x = durP1)) + geom_density(color="red",trim=TRUE) +xlim(c(0,3446407))+ labs(title="durP1/durP2 densities (red/blue)") + geom_density(aes(x = durP2),color="blue",trim=TRUE)
print(p1)

p1<-ggplot(dat, aes(x = durP1)) + stat_density() +xlim(c(0,3446407))+ labs(title="durP2 density")
print(p1)

p1<-ggplot(dat, aes(x = P25)) + stat_density() + labs(title="P25 density (log scaled)") + scale_x_log10()
print(p1)

p1<-ggplot(dat, aes(x = P25)) + stat_density() + labs(title="P25 density") + xlim(c(2000,8000))
print(p1)

p1<-ggplot(dat, aes(x = P10)) + stat_density() + labs(title="P10 density") + xlim(c(8000,30000))
print(p1)

p1<-ggplot(dat, aes(x = P25)) + stat_density() + labs(title="P25 density/location_id") + xlim(c(2000,8000))+ facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = P10)) + stat_density() + labs(title="P10 density/location_id") + xlim(c(8000,30000))+ facet_wrap(~location_id)
print(p1)

p1<-ggplot(dat, aes(x = P25)) + geom_density(aes(x = durP2),color="black",trim=TRUE) + labs(title="P25 (black), P10 (blue) densities") + xlim(c(0,50000))+ geom_density(aes(x = P10),color="blue",trim=TRUE)
print(p1)


p1<-ggplot(dat, aes(x = dust_density)) + geom_bar()+ labs(title="dust_density histogram") + xlim(c(-0.01,0.08)); print(p1)

p1<-ggplot(dat, aes(x = P10)) + stat_density() + labs(title="P10 density/sensor type") + xlim(c(8000,30000))+ facet_wrap(~type)
print(p1)


p1 <- ggplot(filter(dat, type=="PPD42NS"), aes(P1, P2)) + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(~location_id)
print(p1)

p1 <- ggplot(filter(dat, type=="PPD42NS"), aes(P1, P2,color=as.double(timestamp2))) + scale_colour_continuous(high="yellow") + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(~location_id)
print(p1)

p1 <- ggplot(dat, aes(P25, P10)) + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)
print(p1)

p1 <- ggplot(dat, aes(P1, P2)) + geom_point() +scale_x_log10() + scale_y_log10() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)
print(p1)

p1 <- ggplot(dat, aes(ratioP1, ratioP2)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)  +scale_x_log10() + scale_y_log10()
print(p1)

p1 <- ggplot(dat, aes(durP1, durP2)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE) #+scale_x_log10() + scale_y_log10()
print(p1)

p1 <- ggplot(dat, aes(vo_raw, voltage)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)  #+scale_x_log10() + scale_y_log10()
print(p1)

p1 <- ggplot(dat, aes(timestamp2, P1)) + geom_point() + facet_wrap(type~location_id, drop=TRUE,shrink=TRUE)  + scale_y_log10()
print(p1)

p1 <- ggplot(dat) + geom_line(aes(timestamp2, P1)) + geom_line(aes(timestamp2, P2, color="red")) + facet_wrap(type~location_id,ncol=1, drop=TRUE,shrink=TRUE)  + scale_y_log10()
print(p1)

# measurement times
p1 <- ggplot(dat) + geom_density(aes(x = timestamp2),color="blue",trim=TRUE,kernel="rectangular",width=0.1) + labs(title="Measurement density")
print(p1)

p1<- ggplot(dat) + geom_point(aes(timestamp2,P2,order = sample(seq_along(timestamp2))))
print(p1)

# since we do have dplyr and count, plot the "table" data
# TODO: make this work
# p1<-ggplot(count(dat,yday=as.POSIXlt(dat$timestamp2)$yday,type),aes(yday,n,col=type)) + geom_point()
# print(p1)

dev.off() # end plot to pdf

##random sample for histogram
#rand.ppd <- sample_n(ppd, 1000)
#p2 <- ggplot(data=filter(dat, type=="PPD42NS"), aes(P2)) + geom_histogram(binwidth=1/10)

##Daten fuer Sensoren anschauen
#head(dat)
#sample_n(filter(dat, type=="PPD42NS"), 10)
#sample_n(filter(dat, type=="GP2Y1010AU0F"), 10)

## some statistics about measurements
# look with table
# yday = day of year
table(dat$type,as.POSIXlt(dat$timestamp2)$yday,useNA = "ifany")

# how many NA's in P2?
table(dat$type,as.POSIXlt(dat$timestamp2)$yday,sapply(dat$P2,is.na),useNA = "no")
# how many NA's in P1?
table(dat$type,as.POSIXlt(dat$timestamp2)$yday,sapply(dat$P1,is.na),useNA = "no")

## official data sets

source("readdata_s_mitte.R")

if(!("sdat" %in% ls())){ # check if we have the data
    warning("data not found, check readdata_s_mitte.R to download")
    }else{ # plot
    pdf("s-mitte.pdf",width=20, height=8)
    for (y in names(sdat)[3:length(names(sdat))]){
        p<-ggplot(sdat)+
            geom_line(aes_string("datelt",y))+
            labs(x="Zeit",
                 y=attr(sdat,"ylabel")[attr(sdat,"names")==y])
        print(p)
    }
    # can you see sylvester? PMx > 500 
    # lets leave that out
    y="pm25"
    p<-ggplot(sdat[sdat$datelt>as.POSIXlt("2015-01-01 08:00:00"),])+
        geom_line(aes_string("datelt",y))+
        labs(title="Ohne Sylvester",
             x="Zeit",
             y=attr(sdat,"ylabel")[attr(sdat,"names")==y])
    
    # PM10 daily means (Tagesmittelwerte), threshold is 50mug
    sdat.yday<-aggregate(select(sdat,date,pm10),by=list(yday=sdat$datelt$yday),mean)
    sdat.yday$datelt=as.POSIXlt(sdat.yday$date)
    sdat.yday$above50<-factor(sdat.yday$pm10>50)
    print(p) 
    
    y="pm10"
    p<-ggplot(sdat[sdat$datelt>as.POSIXlt("2015-01-01 08:00:00"),])+
        geom_line(aes_string("datelt",y))+
        labs(title=paste("Ohne Sylvester, ??berschreitungen:",sum(sdat.yday$pm10>50,na.rm=TRUE)),
             x="Zeit",
             y=attr(sdat,"ylabel")[attr(sdat,"names")==y])+
        geom_point(data=sdat.yday,
                   aes(datelt,pm10,color=above50),size=5)+
        scale_colour_discrete(h = c(120, 340), c = 100, l = 65, h.start = 30, direction = 1, na.value = "grey50")+
        geom_hline(yintercept=50,lty=2) 

    print(p) 
    dev.off()
} #  end if sdat
