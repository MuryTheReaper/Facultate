package domain;

import javafx.beans.binding.DoubleExpression;

import java.time.LocalDate;
import java.util.Date;

public class SpecialOffer extends Entity<Double>{

    private Double hotelId;

    private Date startDate;

    private Date endDate;

    private int percents;

    public SpecialOffer(Double hotelId, Date startDate, Date endDate, int percents) {
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public Date getStartDate() {
        return startDate;
    }

    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    public Date getEndDate() {
        return endDate;
    }

    public void setEndDate(Date endDate) {
        this.endDate = endDate;
    }

    public int getPercents() {
        return percents;
    }

    public void setPercents(int percents) {
        this.percents = percents;
    }
}
