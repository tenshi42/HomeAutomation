import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

const httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable({
  providedIn: 'root'
})
export class HTTPAPIService {

  constructor(private http: HttpClient) { }

  get(url) {
    console.log('send : ' + url);
    this.http.get(url).subscribe((data) => {console.log(data); } );
    return 'nulllll';
    return this.http.get(url);
  }
}
