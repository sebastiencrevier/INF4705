library(readr)
library(ggplot2)

#get the file and convert result in number
results<-read_csv("results.csv")
results$TempsMoyen=as.numeric(results$TempsMoyen)
results$N=as.numeric(results$N)

#Create graph for each algo with each test

### COUNTING SORT ###
counting_sort<-subset(results, Algorithme == "counting_sort")
series=1:3
for (i in series){ 
  temp <- counting_sort[counting_sort$serie==series[i],]
  if(is.data.frame(temp) && nrow(temp)!=0){
    
    titre=paste("Counting sort - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Counting sort - Test puissance - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    title(main = titre)
    dev.off()
    
    titre= paste("Counting sort - Test rapport - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/N) ~ (N)))
    title(main = titre)
    dev.off()
    
    #TODO : j'arrive pas a trouver comment implémenter ce test la
    #titre="Counting sort - Serie 1 - Test Constantes"
    #jpeg(titre)
    #with(temp, plot((f(TempsMoyen)) ~ (N)))
    #title(main = titre)
    #dev.off()
    
  }

}

### QUICK SORT FP ###
quicksort_fp<-subset(results, Algorithme == "quicksort_fp")
series=1:3
for (i in 1:3){ 
  temp <- quicksort_fp[quicksort_fp$serie==series[i],]
  if(is.data.frame(temp) && nrow(temp)!=0){
    
    titre=paste("Quicksort FP - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quicksort FP - Test puissance - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort FP - Test rapport meilleur cas-cas moyen - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort FP - Test rapport pire cas - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    title(main = titre)
    dev.off()
    
    
    #TODO : j'arrive pas a trouver comment implémenter ce test la
    #titre="Counting sort - Serie 1 - Test Constantes"
    #jpeg(titre)
    #with(temp, plot((f(TempsMoyen)) ~ (N)))
    #title(main = titre)
    #dev.off()
    
  }
  
}

### QUICK SORT FP T ###
quicksort_fp_t<-subset(results, Algorithme == "quicksort_fp_t")
series=1:3
for (i in series){ 
  temp <- quicksort_fp_t[quicksort_fp_t$serie==series[i],]
  if(is.data.frame(temp) && nrow(temp)!=0){
    
    titre=paste("Quicksort FP seuil - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quicksort FP seuil - Test puissance - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort FP seuil - Test rapport meilleur cas-cas moyen - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort FP seuil - Test rapport pire cas - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    title(main = titre)
    dev.off()
  
    
    #TODO : j'arrive pas a trouver comment implémenter ce test la
    #titre="Counting sort - Serie 1 - Test Constantes"
    #jpeg(titre)
    #with(temp, plot((f(TempsMoyen)) ~ (N)))
    #title(main = titre)
    #dev.off()
    
  }
  
}

### QUICK SORT RP ###
quicksort_rp<-subset(results, Algorithme == "quicksort_rp")
series=1:3
for (i in series){ 
  temp <- quicksort_rp[quicksort_rp$serie==series[i],]
  if(is.data.frame(temp) && nrow(temp)!=0){
    
    titre=paste("Quicksort RP - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quicksort RP - Test puissance - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort RP - Test rapport meilleur cas-cas moyen - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort RP - Test rapport pire cas - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    title(main = titre)
    dev.off()

    
    #TODO : j'arrive pas a trouver comment implémenter ce test la
    #titre="Counting sort - Serie 1 - Test Constantes"
    #jpeg(titre)
    #with(temp, plot((f(TempsMoyen)) ~ (N)))
    #title(main = titre)
    #dev.off()
    
  }
  
}

### QUICK SORT RP T ###
quicksort_rp_t<-subset(results, Algorithme == "quicksort_rp_t")
series=1:3
for (i in series){ 
  temp <- quicksort_rp_t[quicksort_rp_t$serie==series[i],]
  if(is.data.frame(temp) && nrow(temp)!=0){
    
    titre=paste("Quicksort RP seuil - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm,col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quicksort RP seuil - Test puissance - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort RP seuil - Test rapport meilleur cas-cas moyen - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    title(main = titre)
    dev.off()
    
    titre= paste("Quicksort RP seuil - Test rapport pire cas - S",i,sep='')
    jpeg(paste(getwd(),"/results/",titre,'.jpg',sep=''))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    title(main = titre)
    dev.off()
    
    #TODO : j'arrive pas a trouver comment implémenter ce test la
    #titre="Counting sort - Serie 1 - Test Constantes"
    #jpeg(titre)
    #with(temp, plot((f(TempsMoyen)) ~ (N)))
    #title(main = titre)
    #dev.off()
    
  }
  
}


