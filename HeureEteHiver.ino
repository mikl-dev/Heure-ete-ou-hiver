uint8_t jourUTC = 31;
uint8_t moisUTC = 6;
uint8_t anneeUTCnormal = 2021;
uint8_t anneeUTC = 2021-2000;  //garder le format 2 chiffres
uint8_t heureUTC = 1; // 1 pour 1 heure du matin

void setup()
{
  Serial.begin(115200);
  Serial.println(String(jourUTC) + " " + moisUTC + " " + String(anneeUTC));
  Serial.println(periodeEte(anneeUTC, moisUTC, jourUTC, heureUTC));

}

void loop()
{


}

bool periodeEte(uint8_t anneeUTC, uint8_t moisUTC, uint8_t jourUTC, uint8_t heureUTC)
{
  //En France métropolitaine :
  //1: ete    Passage de l'heure d'hiver à l'heure d'été le dernier dimanche de mars à 1h00 UTC (à 2h00 locales il est 3h00)
  //0: hiver  Passage de l'heure d'été à l'heure d'hiver le dernier dimanche d'octobre à 1h00 UTC (à 3h00 locales il est 2h00)
  const byte MARS = 3;
  const byte OCTOBRE = 10;
  if (moisUTC == MARS)
  {
    uint8_t dernierDimancheMars = 31 - ((5 + anneeUTC + (anneeUTC >> 2)) % 7); //Pas évidente à trouver celle-là
    return jourUTC > dernierDimancheMars || (jourUTC == dernierDimancheMars && heureUTC != 0);
  }												
  if (moisUTC == OCTOBRE)						
  {
    uint8_t dernierDimancheOctobre = 31 - ((2 + anneeUTC + (anneeUTC >> 2)) % 7);
    return jourUTC < dernierDimancheOctobre || (jourUTC == dernierDimancheOctobre && heureUTC == 0);
  } 
  return MARS < moisUTC && moisUTC < OCTOBRE;   //  -> ajouter le resultat a UTC ((utc+1) + return
  //	  leve conc < now conc  &&   now conc  <  couche conc     -> si 0-> pas de photos, Si 1> photo
}				                 
