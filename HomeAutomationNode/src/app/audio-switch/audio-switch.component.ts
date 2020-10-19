import { Component, OnInit } from '@angular/core';
import { HTTPAPIService } from '../httpapi.service';
import { ConstantesService } from '../constantes.service';

@Component({
  selector: 'app-audio-switch',
  templateUrl: './audio-switch.component.html',
  styleUrls: ['../baseStyle.css', './audio-switch.component.css']
})
export class AudioSwitchComponent implements OnInit {

  constructor(private httpApi: HTTPAPIService, private constantes: ConstantesService) { }

  BASE_DEVICE_PATH = '/AudioSwitch';
  BASE_URL = this.constantes.BASE_API_URL + ':' + this.constantes.BASE_API_PORT + this.BASE_DEVICE_PATH;

  ngOnInit() {
  }

  SetChanels(rightChanel: number, leftChanel: number) {
    this.httpApi.get(
       this.BASE_URL + '/SetChannels/' + (rightChanel) + (leftChanel)
    );
  }
  
  SwitchBluetoothState() {
	this.httpApi.get(
       this.BASE_URL + '/SwitchBluetoothState'
    );
  }
}
