library(readr)

#get the file and convert result in number
results<-read_csv("~/INF4705/TP1/results.csv")
results$TempsMoyen=as.numeric(results$TempsMoyen)
results$N=as.numeric(results$N)

#Create graph for each algo with each test

### COUNTING SORT ###
counting_sort<-subset(results, Algorithme == "counting_sort")
series=1:3
for (i in series){ 
  temp <- counting_sort[counting_sort$serie==series[i],]
  if(is.data.frame(temp) && nrow(temp)!=0){
    
    titre=paste("Counting sort - Serie ",i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Counting sort - Test Puissance - Serie ", i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    abline(lm, col="blue",untf=TRUE)
    title(main = titre)
    dev.off()
    
    titre= paste("Counting sort - Test Rapport - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/N) ~ (N)))
    abline(lm, col="blue")
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
    
    titre=paste("Quick sort FP - Serie ",i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quick sort FP - Test Puissance - Serie ", i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    abline(lm, col="blue",untf=TRUE)
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort FP - Test Rapport Meilleur Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort FP - Test Rapport Pire Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort FP - Test Rapport Cas Moyen - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
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
    
    titre=paste("Quick sort FP avec seuil - Serie ",i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quick sort FP avec seuil- Test Puissance - Serie ", i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    abline(lm, col="blue",untf=TRUE)
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort FP avec seuil- Test Rapport Meilleur Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort FP avec seuil- Test Rapport Pire Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort FP avec seuil- Test Rapport Cas Moyen - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
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
    
    titre=paste("Quick sort RP - Serie ",i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quick sort RP - Test Puissance - Serie ", i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    abline(lm, col="blue",untf=TRUE)
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort RP - Test Rapport Meilleur Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort RP - Test Rapport Pire Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort RP - Test Rapport Cas Moyen - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
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
    
    titre=paste("Quick sort RP avec seuil - Serie ",i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    lm = lm(TempsMoyen ~ N, data=temp)
    with(temp, plot((TempsMoyen) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre=paste("Quick sort RP avec seuil- Test Puissance - Serie ", i)
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen) ~ (N),log="xy"))
    abline(lm, col="blue",untf=TRUE)
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort RP avec seuil- Test Rapport Meilleur Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N*log(N))) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort RP avec seuil- Test Rapport Pire Cas - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
    title(main = titre)
    dev.off()
    
    titre= paste("Quick sort RP avec seuil- Test Rapport Cas Moyen - Serie ", i) 
    jpeg(paste("~/INF4705/TP1/img/",titre))
    with(temp, plot((TempsMoyen/(N^2)) ~ (N)))
    abline(lm, col="blue")
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


