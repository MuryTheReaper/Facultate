package service;

import domain.Client;
import domain.Hotel;
import domain.Location;
import domain.SpecialOffer;

import java.util.Date;
import java.util.List;

public class MasterService {

    private final LocationService locationService;

    private final HotelService hotelService;

    private final SpecialOfferService specialOfferService;

    private final ClientService clientService;

    public MasterService(LocationService locationService, HotelService hotelService, SpecialOfferService specialOfferService, ClientService clientService) {
        this.locationService = locationService;
        this.hotelService = hotelService;
        this.specialOfferService = specialOfferService;
        this.clientService = clientService;
    }

    public Iterable<Location> getAllLocations(){
        return locationService.findAll();
    }

    public Iterable<Hotel> getAllHotels(){
        return hotelService.findAll();
    }

    public Iterable<SpecialOffer> getHotelOffersByDate(Double id,Date start, Date end){

        List<SpecialOffer> list = (List<SpecialOffer>) specialOfferService.findAll();

        list.removeIf(sp -> !(sp.getStartDate().after(start) && sp.getEndDate().before(end) && sp.getHotelId().equals(id)));

        return list;

    }

    public Client getClient (Long id){
        return clientService.findOne(id);
    }

    public List<SpecialOffer> getSOClient (Client client){

        List<SpecialOffer> list = (List<SpecialOffer>) specialOfferService.findAll();

        list.removeIf(sp -> sp.getPercents() > client.getFidelityGrade());

        return list;

    }


}
