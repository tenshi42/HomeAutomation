import { Component, OnInit } from '@angular/core';
import { HTTPAPIService } from '../httpapi.service';
import { ConstantesService } from '../constantes.service';

@Component({
  selector: 'app-projector',
  templateUrl: './projector.component.html',
  styleUrls: ['../baseStyle.css', './projector.component.css']
})
export class ProjectorComponent implements OnInit {

  constructor(private httpApi: HTTPAPIService, private constantes: ConstantesService) { }

  BASE_DEVICE_PATH = '/Projector';
  BASE_URL = this.constantes.BASE_API_URL + ':' + this.constantes.BASE_API_PORT + this.BASE_DEVICE_PATH;

  ngOnInit() {
  }

  Power(state: boolean) {
    const ret = this.httpApi.get(
      this.BASE_URL + '/Power/' + (state ? '1' : '0')
    );
    console.log('get : ' + JSON.stringify(ret));
  }
}
